
import numpy as np
import glob
import os, sys
import argparse
import re
import sys

c_results = []
h_results = []

io_addr_find = []

io_list_layer_name = []
io_list_out_name   = []
io_list_count = []
io_list_size = []

def parse_args():
    """
    Parse input arguments
    """
    parser = argparse.ArgumentParser(description='Mapper code convert for DQ1 EVB')
    parser.add_argument('--cfile', dest='c_file',
                        help='C code file name',
                        default='test.c', type=str)

    parser.add_argument('--hfile', dest='h_file',
                        help='H header file name',
                        default='test.h', type=str)

    parser.add_argument('--ofile', dest='o_file', 
                        help='InOut information file', 
                        default='inout_info.txt', type=str)

    parser.add_argument('--rfile', dest='r_file', 
                        help='Run file', 
                        default='run.txt', type=str)

    if len(sys.argv) == 1:
        parser.print_help()
        sys.exit(1)

    args = parser.parse_args()
    return args

def file_parse_io_info(o_file_name):
    f_io = open(o_file_name)

    lines = f_io.readlines()
    out_counter = 0;
    for line in lines:
        if 'OUTPUT_NAME=' in line:
            line = line.replace("OUTPUT_NAME=", "")
            line = line.replace("\n","")
            names = line.split(",")

            if len(names) == 1:
                io_list_layer_name.append(names[0])
                if out_counter == 0:
                    outname = "ltable.output_addr"
                else:
                    outname = "ltable.ext_inout_addr[" + str(out_counter-1) + "]"
                io_list_out_name.append(outname)
                out_counter += 1
                io_list_count.append(str(1))
            else:
                if out_counter == 0:
                    outname = "ltable.output_addr"
                else:
                    outname = "ltable.ext_inout_addr[" + str(out_counter-1) + "]"
                out_counter += 1
                for i in range(len(names)):
                    io_list_layer_name.append(names[i])
                    io_list_out_name.append(outname)
                    io_list_count.append(len(names))

#    print(io_list_layer_name)
#    print(io_list_out_name)
#    print(io_list_count)

    f_io.close()

def file_parse_r_file(r_file_name):
    f_r = open(r_file_name)

    lines = f_r.readlines()

    out_counter = 0
    while out_counter < len(io_list_layer_name):
        repeat_layers = int(io_list_count[out_counter])
        if repeat_layers > 1:
            for i in range(repeat_layers-1):
                line_idx = 0
                while line_idx < len(lines):
                    if lines[line_idx].find(io_list_layer_name[out_counter]) > -1:
                        io_list_size.append(re.findall("\d+", lines[line_idx+2])[1])
                        line_idx += 2
                    else:
                        line_idx+=1
            io_list_size.append(str(0))
            #Shift values
            idx = out_counter + repeat_layers - 1
            while idx > out_counter:
                io_list_size[idx] = io_list_size[idx-1]
                idx -= 1
            io_list_size[out_counter] = '0'
            out_counter += repeat_layers
        else:
            io_list_size.append(str(0))
            out_counter += 1

#    print(io_list_size)

    f_r.close()

def file_convert_h(h_file_name):
#    print ('H file name: ', h_file_name)

    f_h = open(h_file_name)
    h_lines = f_h.readlines()

    for line in h_lines:
        result_mod = line

        result_mod = result_mod.replace("#define DDR_BASE", "#undef DDR_BASE //")
        result_mod = result_mod.replace("#ifndef DDR_BASE", "#ifdef DDR_BASE")

 #       print ('H results', result_mod)
        h_results.append(result_mod)


    h_conv_file_name = h_file_name[:-2] + '_EVB.h'
#    print ('Write H file name: ', h_conv_file_name)
    f_conv_h = open(h_conv_file_name, 'w')

    N = len(h_results)
    for i in range(N):
#        print(h_results[i])
        f_conv_h.write(h_results[i])

        if i == (N-1):
 #           print("Save: ", h_results[i][8:-12])
            io_addr_find.append(h_results[i][8:-12])

    f_h.close()
    f_conv_h.close()



def file_convert_c(c_file_name, h_file_name, o_file_name):
    print ('C file name: ', c_file_name)
    print ('H file name: ', h_file_name)

    f_c      = open(c_file_name)
    f_h      = open(h_file_name)
    f_o      = open(o_file_name)

    c_lines      = f_c.readlines()

    flag_boundary = 0
    for line in c_lines:
        result_mod = line
        is_set_out_name = 0

        # 0) h_file include -> _EVB.h
        result_mod = result_mod.replace(h_file_name[:-2], h_file_name[:-2] + '_EVB')

        # 1) '#define NULLADDR 0x0' case
        #     - #define NETWORK_STAT(x) nmp_csr_write(NMP_REG_GPR1, x)'
        #     - nmp_dma_table_parse2 insert
        if ('#define NULLADDR 0x0' in result_mod):
            c_results.append(result_mod)
            c_results.append("#define NETWORK_STAT(x) nmp_csr_write(NMP_REG_GPR1, x)\n")
#            print ('[C results]', result_mod)
            continue

        # 2) 'int main' case
        #     - uint32 DDR_BASE = 0x0;
        #     - uint32 PARAM_BASE = 0x0;
        #     - uint32 INPUT_BASE= 0x0;
        #     - uint32 OUTPUT_BASE = 0x0;
        if ('int main' in result_mod):
            c_results.append(result_mod)
#            print ('[C results]', result_mod)
            continue

        # 3) 'uint16 tle_id = nmp_tle_id'  case
        #      - \n
        #      - NETWORK_STAT(0x1);
        #      - nmp_sync_layer_boundary_EVB( tlt_id, tle_id, 0, 0, 4, 8, 1 );
        #      - nmp_dma_table_parse2(&DDR_BASE, &PARAM_BASE, &INPUT_BASE, &OUTPUT_BASE);
        if ("nmp_tle_id" in result_mod):
            c_results.append(result_mod)
#            print ('[C results]', result_mod)

            c_results.append("\n")
            c_results.append("    struct nmp_ipc_table ltable;\n")
            c_results.append("\n")
            c_results.append("    NETWORK_STAT(0x1);\n")
            c_results.append("    nmp_sync_layer_boundary_EVB( tlt_id, tle_id, 0, 0, 4, 8, 0 );\n")
            c_results.append("\n")
            c_results.append("    nmp_ipc_table_parse_multi(&ltable);\n")
            continue

        # 4) 'DATA__DATA__FEATUREMAP__DATA' case
        #       - INPUT BASE address
        if 'PARAM_OFFSET + DATA__' in result_mod:
            c_results.append("                ltable.input_addr,\n")
            continue
        elif 'PARAM_OFFSET + IMAGEDATA__' in result_mod:
            c_results.append("                ltable.input_addr,\n")
            continue

        # 5) DDR_BASE + PARAM_OFFSET -> PARAM_BASE
        result_mod = result_mod.replace("DDR_BASE + PARAM_OFFSET", "ltable.param_addr")

        # 6) nmp_sync_layer_boundary -> nmp_sync_layer_boundary_EVB
        if ("nmp_sync_layer_boundary" in result_mod and flag_boundary == 1):
          result_mod = result_mod.replace("nmp_sync_layer_boundary", "nmp_sync_layer_boundary_EVB")
        elif ("nmp_sync_layer_boundary" in result_mod and flag_boundary == 0):
          flag_boundary = 1          
          result_mod = ""

        # 7) ' last layer output address' case
        #    - Output BASE address
        if len(io_list_layer_name) == 1:
#            print("io_addr_find:", io_addr_find[0])
            if io_addr_find[0] in result_mod:
                c_results.append("                 ltable.output_addr,\n")
                continue
        else:
            for i in range(len(io_list_layer_name)):
                pattern = "FEATUREMAP__" + io_list_layer_name[i].upper()
                if line.find(pattern) > -1:
 #                   print("HIT!!!!! - ", pattern)
                    if int(io_list_size[i]) > 0:
                        out_str = "                " + io_list_out_name[i] + "+" + str(int(io_list_size[i])*2) + ",\n"
                    else:
                        out_str = "                " + io_list_out_name[i] + ",\n"
                    c_results.append(out_str)
                    is_set_out_name = 1
                continue

        # 8) 'nmp_halt( NMP_HALT_INT, 0x1 );'  case
        #    - NETWORK_STAT(0x0);
        #    - nmp_halt( NMP_HALT_INT, 0x1 );
        if ("nmp_halt( NMP_HALT_INT, 0x1 )" in result_mod):
            c_results.append("    NETWORK_STAT(0x0);\n")
            c_results.append("    nmp_halt( NMP_HALT_INT, 0x1 );\n")

            continue

        if is_set_out_name != 1:
#            print ('[C results]', result_mod)
            c_results.append(result_mod)

    for line in c_lines:
        result_mod = line

    c_conv_file_name = c_file_name[:-2] + '_EVB.c'
#    print ('Write C file name: ', c_conv_file_name)
    f_conv_c = open(c_conv_file_name, 'w')

    N = len(c_results)
    for i in range(N):
#        print(c_results[i])
        f_conv_c.write(c_results[i])

    f_c.close()
    f_h.close()
    f_o.close()

    f_conv_c.close()

if __name__=='__main__':
    args = parse_args()
    print('Called with args:')
    print(args)

    c_file_name = args.c_file
    h_file_name = args.h_file
    o_file_name = args.o_file
    r_file_name = args.r_file

    file_parse_io_info(o_file_name)
    file_parse_r_file(r_file_name)
    file_convert_h(h_file_name)
    file_convert_c(c_file_name, h_file_name, o_file_name)

