import argparse
import os

def main(name, run_nmp, param_file):
	run_file = open(run_nmp, 'r')

	result_file = open('output/{0}/validator_inform.cfg'.format(name), 'w+')	
	#result_file = open('validator_inform.cfg', 'w+')

	lowercase_name = name.lower()

	lines = run_file.readlines()
	print("TEST_NAME={0}".format(lowercase_name), file = result_file)
	print("PARAM_SIZE={0}\n".format(os.path.getsize(param_file)), file = result_file)


	for line in lines:
#		if ("L2_OUT_" in line):
#			continue
		if ("OUT_NAME=" in line):
			print(line.strip(), file = result_file)
		elif ("OUT_SIZE=" in line):
			print(line.strip(), file = result_file)
		elif ("OUT_ADDR=" in line):
			tmp_line = line.split("=")			
			hex_to_decimal = int(tmp_line[1], 16) #16777216
			print("{0}={1}".format(tmp_line[0], hex_to_decimal - 16777216), file = result_file)
			#print("{0}  hex_to_decimal : {1}  six_hex_digit_to_decimal : {2}".format(line.strip(), hex_to_decimal, hex_to_decimal - 16777216), file = result_file)
		elif ("OUT_W=" in line):
			print(line.strip(), file = result_file)
		elif ("OUT_H=" in line):
			print(line.strip(), file = result_file)
		elif ("OUT_CH=" in line):
			print(line.strip(), file = result_file)
		elif ("OUT_Q=" in line):
			print(line, file = result_file)


if __name__ == "__main__":
	parser = argparse.ArgumentParser()
	parser.add_argument('-n', help="Test dir name(ex> LeNet)")
	parser.add_argument('-r', help="runscript path(ex> run_nmp_net_xxx)")
	parser.add_argument('-p', help="parameter path(ex> nmp_param_xxx.bin)")
	args = parser.parse_args()
	main(args.n, args.r, args.p)


