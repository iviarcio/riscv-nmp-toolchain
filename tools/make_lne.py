# Copyright 2018 LG Electoronics All rights reserved.

import os
import sys
import argparse
import numpy as np
import copy
sys.path.append(os.path.join(os.path.dirname(__file__), './flatbuffers/python/'))
#sys.path.append(os.path.join(os.path.dirname(__file__), '../../../../tools/make/downloads/flatbuffers/python/'))
import flatbuffers
import tflite.Model
import tflite.Buffer
import tflite.Operator
import tflite.SubGraph
import tflite.TensorType
import tflite.Tensor
import tflite.OperatorCode
import tflite.OneShotOptions
import tflite.BuiltinOptions
import tflite.BuiltinOperator
import tflite.mean_vec

def main(firmware, parameter, runscript, mean, scale, input_type, data_format):
    # data for .lne schema
    lne_version = 3
    fsize = 0
    psize = 0
    bsize = 0
    input_shape = [0, 0, 0, 0]
    output_shape = [0, 0, 0, 0]
    inputq = 0
    outputq = 0
    mean_b = float(mean[0])
    mean_g = float(mean[1])
    mean_r = float(mean[2])
    num_layer = 0
    LAYERS = []
    output_type = "FLOAT32"
    attr = {'name': '', 'size' : 0, 'w' : 0, 'h' : 0, "c" : 0, "n" : 0, "qmode" : "", "outq" : 0}
    with open(firmware, "rb") as f:
        firmware_buf = f.read()
        fsize = f.tell()

    with open(parameter, "rb") as w:
        parameter_buf = w.read()
        psize = w.tell()

    # bsize, inputq, outputq
    # TODO: parsing run_nmp_script
    lines = open(runscript).readlines()
    for line in lines:
        str_temp = "".join(line.strip(' \t\n\r'))
        temp = str_temp.split("=")
        if line[0] == "L":
            ts = len(temp[0])
            if temp[0][ts - len("NAME"):] == "NAME":
                attr['name'] = temp[1]
            if temp[0][ts - len("SIZE"):] == "SIZE":
                attr['size'] = int(temp[1])
            if temp[0][ts - len("_W"):] == "_W":
                attr['w'] = int(temp[1])
            if temp[0][ts - len("_H"):] == "_H":
                attr['h'] = int(temp[1])
            if temp[0][ts - len("_CH"):] == "_CH":
                attr['c'] = int(temp[1])
            if temp[0][ts - len("_NUM"):] == "_NUM":
                attr['n'] = int(temp[1])
            if temp[0][ts - len("QMODE"):] == "QMODE":
                attr['qmode'] = temp[1]
                num_layer=num_layer + 1								
            if temp[0][ts - len("Q"):] == "Q":
                attr['outq'] = int(temp[1])
                attr_temp = copy.deepcopy(attr)
                LAYERS.append(attr_temp)
                #print(LAYERS)
#        if temp[0] == "NUM_LAYERS":
#            num_layer = int(temp[1])

    print("NUM_LAYER : ", num_layer)
    inputq = LAYERS[0]["outq"]
    outputq = LAYERS[num_layer-1]['outq']

    for i in range(2, num_layer):
        bsize = bsize + LAYERS[i]['size']

    # if QMODE is fxp16
#    bsize = bsize * 2  
    if data_format == "NHWC":
        input_shape = [LAYERS[0]['n'], LAYERS[0]['h'], LAYERS[0]['w'], LAYERS[0]['c']]
    elif data_format == "NCHW":
        input_shape = [LAYERS[0]['n'], LAYERS[0]['c'], LAYERS[0]['h'], LAYERS[0]['w']]
    else:
        print("not support data format: ", data_format)
        sys.exit(1);

    if data_format == "NHWC":
        output_shape = [LAYERS[num_layer - 1]['n'], LAYERS[num_layer - 1]['h'], LAYERS[num_layer - 1]['w'], LAYERS[num_layer -1]['c']]
    elif data_format == "NCHW":
        output_shape = [LAYERS[num_layer - 1]['n'], LAYERS[num_layer - 1]['c'], LAYERS[num_layer - 1]['h'], LAYERS[num_layer -1]['w']]
    else:
        print("not support data format: ", data_format)
        sys.exit(1);

    if fsize >= 1024*1024:
        print("firmware size is bigger than 1MB ", firmware, ",firmware size: ", fsize)
        print("DO NOT USE THIS FIRMWARE !!, Report to SIC(dq1-dev@lge.com)")
        print("DO NOT USE THIS FIRMWARE !!, Report to SIC(dq1-dev@lge.com)")
        print("DO NOT USE THIS FIRMWARE !!, Report to SIC(dq1-dev@lge.com)")
        print("DO NOT USE THIS FIRMWARE !!, Report to SIC(dq1-dev@lge.com)")
        print("DO NOT USE THIS FIRMWARE !!, Report to SIC(dq1-dev@lge.com)")
        sys.exit(1);

 # TODO : 64Mb  
    if fsize + psize + bsize >= 240*1024*1024:
        print("Total file size exceeds 240MB, needs to do something")		
        print("DO NOT USE THIS FIRMWARE !!, Report to SIC(dq1-dev@lge.com)")
        print("DO NOT USE THIS FIRMWARE !!, Report to SIC(dq1-dev@lge.com)")
        print("DO NOT USE THIS FIRMWARE !!, Report to SIC(dq1-dev@lge.com)")
        print("DO NOT USE THIS FIRMWARE !!, Report to SIC(dq1-dev@lge.com)")
        print("DO NOT USE THIS FIRMWARE !!, Report to SIC(dq1-dev@lge.com)")


    print("LNE excute information")
    print("firmware: ", firmware, ",firmware size: ", fsize)
    print("parameter: ", parameter, ",parameter size: ", psize)
    print("The number of layers: ", num_layer)
    print("Internal buffer size:", bsize)
    print("input info")
    print("input shape: ", input_shape)
    print("input Q: ", inputq)
    print("input type: ", input_type)
    print("input mean value(bgr order) ", mean_b, mean_g, mean_r)
    print("input scale: ", scale)
    print("output info")
    print("output shape: ", output_shape)
    print("output Q: ", outputq)
    print("output type: ", output_type)

    builder = flatbuffers.Builder(8102)
    lne_desc = builder.CreateString('Flatbuffer for lne')
    sub_desc = builder.CreateString('Test SubGraph0')
    firm_name = builder.CreateString('firmware')
    param_name = builder.CreateString('parameter')
    input_name = builder.CreateString('input')
    output_name = builder.CreateString('output')
    firm_vector = builder.CreateByteVector(bytearray(firmware_buf))
    param_vector = builder.CreateByteVector(bytearray(parameter_buf))

    # OperaterCode
    tflite.OperatorCode.OperatorCodeStart(builder)
    tflite.OperatorCode.OperatorCodeAddBuiltinCode(builder, tflite.BuiltinOperator.BuiltinOperator().OneShot)
    op103 = tflite.OperatorCode.OperatorCodeEnd(builder)
    tflite.Model.ModelStartOperatorCodesVector(builder, 1)
    builder.PrependUOffsetTRelative(op103)
    lne_op = builder.EndVector(1)

    # sub tensor(firmware, parameter, input, output)
    tflite.Tensor.TensorStartShapeVector(builder, 1)
    builder.PrependInt32(fsize)
    f_shapes = builder.EndVector(1)

    tflite.Tensor.TensorStart(builder)
    tflite.Tensor.TensorAddType(builder, tflite.TensorType.TensorType().UINT8)
    tflite.Tensor.TensorAddBuffer(builder, 1)
    tflite.Tensor.TensorAddShape(builder, f_shapes)
    tflite.Tensor.TensorAddName(builder, firm_name)
    f_tensor = tflite.Tensor.TensorEnd(builder)

    tflite.Tensor.TensorStartShapeVector(builder, 1)
    builder.PrependInt32(psize)
    p_shapes = builder.EndVector(1)

    tflite.Tensor.TensorStart(builder)
    tflite.Tensor.TensorAddType(builder, tflite.TensorType.TensorType().UINT8)
    tflite.Tensor.TensorAddBuffer(builder, 2)
    tflite.Tensor.TensorAddShape(builder, p_shapes)
    tflite.Tensor.TensorAddName(builder, param_name)
    p_tensor = tflite.Tensor.TensorEnd(builder)

    # input shapes
    tflite.Tensor.TensorStartShapeVector(builder, 4)
    builder.PrependInt32(input_shape[3])
    builder.PrependInt32(input_shape[2])
    builder.PrependInt32(input_shape[1])
    builder.PrependInt32(input_shape[0])
    input_shapes = builder.EndVector(4)

    tflite.Tensor.TensorStart(builder)
    tflite.Tensor.TensorAddBuffer(builder, 3)
    tflite.Tensor.TensorAddName(builder, input_name)
    if input_type == "UINT8":
        tflite.Tensor.TensorAddType(builder, tflite.TensorType.TensorType().UINT8)
    elif input_type == "FLOAT32":
        tflite.Tensor.TensorAddType(builder, tflite.TensorType.TensorType().FLOAT32)
    else:
        print("not support input type: ", input_type)
        sys.exit(1);
    tflite.Tensor.TensorAddShape(builder, input_shapes)
    i_tensor = tflite.Tensor.TensorEnd(builder)

    # output shapes
    tflite.Tensor.TensorStartShapeVector(builder, 4)
    builder.PrependInt32(output_shape[3])
    builder.PrependInt32(output_shape[2])
    builder.PrependInt32(output_shape[1])
    builder.PrependInt32(output_shape[0])
    output_shapes = builder.EndVector(4)

    tflite.Tensor.TensorStart(builder)
    tflite.Tensor.TensorAddBuffer(builder, 4)
    tflite.Tensor.TensorAddName(builder, output_name)
    tflite.Tensor.TensorAddType(builder, tflite.TensorType.TensorType().FLOAT32)
    tflite.Tensor.TensorAddShape(builder, output_shapes)
    o_tensor = tflite.Tensor.TensorEnd(builder)

    tflite.SubGraph.SubGraphStartTensorsVector(builder, 4)
    builder.PrependUOffsetTRelative(o_tensor)
    builder.PrependUOffsetTRelative(i_tensor)
    builder.PrependUOffsetTRelative(p_tensor)
    builder.PrependUOffsetTRelative(f_tensor)
    lne_tensor = builder.EndVector(4)


    # sub operator inputs / outputs
    tflite.SubGraph.SubGraphStartInputsVector(builder, 3)
    builder.PrependInt32(1)
    builder.PrependInt32(0)
    builder.PrependInt32(2)
    op_input = builder.EndVector(3)

    tflite.SubGraph.SubGraphStartOutputsVector(builder, 1)
    builder.PrependInt32(3)
    op_output = builder.EndVector(1)

    # oneshot op option
    tflite.OneShotOptions.OneShotOptionsStart(builder)
    tflite.OneShotOptions.OneShotOptionsAddFirmwareSize(builder, fsize)
    tflite.OneShotOptions.OneShotOptionsAddParameterSize(builder, psize)
    tflite.OneShotOptions.OneShotOptionsAddIbufferSize(builder, bsize)
    tflite.OneShotOptions.OneShotOptionsAddInputQ(builder, inputq)
    tflite.OneShotOptions.OneShotOptionsAddOutputQ(builder, outputq)
    tflite.OneShotOptions.OneShotOptionsAddScale(builder, scale)
    tflite.OneShotOptions.OneShotOptionsAddMean(builder, tflite.mean_vec.Createmean_vec(builder, mean_b, mean_g, mean_r))
    op_option = tflite.OneShotOptions.OneShotOptionsEnd(builder)

    # sub operator
    tflite.Operator.OperatorStart(builder)
    tflite.Operator.OperatorAddOpcodeIndex(builder, 0) # Modify opcode
    tflite.Operator.OperatorAddBuiltinOptionsType(builder, tflite.BuiltinOptions.BuiltinOptions().OneShotOptions)
    tflite.Operator.OperatorAddInputs(builder, op_input)
    tflite.Operator.OperatorAddOutputs(builder, op_output)
    tflite.Operator.OperatorAddBuiltinOptions(builder, op_option)
    lne_op1 = tflite.Operator.OperatorEnd(builder)

    tflite.SubGraph.SubGraphStartOperatorsVector(builder, 1)
    builder.PrependUOffsetTRelative(lne_op1)
    lne_operator = builder.EndVector(1)


    # sub input: buffer_num
    tflite.SubGraph.SubGraphStartInputsVector(builder, 1)
    builder.PrependInt32(2)
    lne_input = builder.EndVector(1)
    # sub ouput: buffer_num
    tflite.SubGraph.SubGraphStartOutputsVector(builder, 1)
    builder.PrependInt32(3)
    lne_output = builder.EndVector(1)

    # Subgraph
    tflite.SubGraph.SubGraphStart(builder)
    tflite.SubGraph.SubGraphAddTensors(builder, lne_tensor)
    tflite.SubGraph.SubGraphAddOperators(builder, lne_operator)
    tflite.SubGraph.SubGraphAddInputs(builder, lne_input)
    tflite.SubGraph.SubGraphAddOutputs(builder, lne_output)
    tflite.SubGraph.SubGraphAddName(builder, sub_desc)
    subgraph0 = tflite.SubGraph.SubGraphEnd(builder)

    tflite.Model.ModelStartSubgraphsVector(builder, 1)
    builder.PrependUOffsetTRelative(subgraph0)
    lne_subgraph = builder.EndVector(1)

    # BUFFER
    tflite.Buffer.BufferStart(builder)
    buf_free = tflite.Buffer.BufferEnd(builder)

    tflite.Buffer.BufferStart(builder)
    buf_input = tflite.Buffer.BufferEnd(builder)

    tflite.Buffer.BufferStart(builder)
    buf_output = tflite.Buffer.BufferEnd(builder)

    tflite.Buffer.BufferStart(builder)
    tflite.Buffer.BufferAddData(builder,firm_vector)
    buf_firmware = tflite.Buffer.BufferEnd(builder)

    tflite.Buffer.BufferStart(builder)
    tflite.Buffer.BufferAddData(builder, param_vector)
    buf_parameter = tflite.Buffer.BufferEnd(builder)

    tflite.Model.ModelStartBuffersVector(builder, 5)
    builder.PrependUOffsetTRelative(buf_output)
    builder.PrependUOffsetTRelative(buf_input)
    builder.PrependUOffsetTRelative(buf_parameter)
    builder.PrependUOffsetTRelative(buf_firmware)
    builder.PrependUOffsetTRelative(buf_free)
    lne_buffers = builder.EndVector(5)

    # MODEL root
    tflite.Model.ModelStart(builder)
    tflite.Model.ModelAddVersion(builder, lne_version)
    tflite.Model.ModelAddOperatorCodes(builder, lne_op)
    tflite.Model.ModelAddSubgraphs(builder, lne_subgraph)
    tflite.Model.ModelAddBuffers(builder, lne_buffers)
    tflite.Model.ModelAddDescription(builder, lne_desc)

    lne_orc = tflite.Model.ModelEnd(builder)

    builder.Finish(lne_orc)
    buf = builder.Output()


#    temp = runscript.split('_')  #output/"NAME"/firmware/run_nmp_net_"NAME"_(EVB)
#    temp_len = len(temp) 
#    temp_index = temp.index("net") + 1
#    out_filename = ""		
#    while temp[temp_index] != "EVB" and temp_index < temp_len:
#      out_filename = out_filename + temp[temp_index] + "_"
#      temp_index = temp_index + 1;     
#    out_filename = out_filename[:-1]

    temp = os.path.basename(runscript)
    out_filename = temp[:-4]
    print("filename : ", out_filename)



    with open(out_filename + ".lne", "wb") as o:
        o.write(buf)

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('-f', help="firmware path(ex> rcrfirm.bin)")
    parser.add_argument('-p', help="parameter path(ex> nmp_net_xxx_parameter.bin)")
    parser.add_argument('-r', help="runscript path(ex> run_nmp_net_xxx)")
    parser.add_argument('-m', nargs="*", help="mean values(channel order) ex> 111.5 117.3 115.6, default: 0.0 0.0 0.0", default= [0.0, 0.0, 0.0], type=float)
    parser.add_argument('-s', help="scale ex>0.017, defaut: 1.0", default=1.0, type=float)
    parser.add_argument('-it', help="input type ex> UINT8/FLOAT32, default: FLOAT32", default="FLOAT32")
    parser.add_argument('-df', help="data format ex> NHWC/NCHW, default: NHWC", default="NHWC")
    args = parser.parse_args()
    main(args.f, args.p, args.r, args.m, args.s, args.it, args.df)
