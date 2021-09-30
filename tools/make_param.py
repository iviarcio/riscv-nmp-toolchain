import os
import argparse
import json

def main(map_path, wbin_path):
#	map_file = open(map_path, "r")
	weight_bin = open(wbin_path, "w+b")
	base_addr = 0x01000000

	with open(map_path, "r") as map_file:
		data = json.load(map_file)

	size = len(data["blob"])
#	print(size)
	
	for i in range(0, size):
#		print("i is ", i)
#		print(data["blob"][i]["file"])
		weight_file = data["blob"][i]["file"]
#		print(type(weight_file))
		weight_file2 = "./params/" + weight_file
		print(weight_file2)
#		print(type(weight_file2))

#		print(data["blob"][i]["offset"])

		addr = int(data["blob"][i]["offset"], 16)
		seek_offset = addr - base_addr
#		print("seek offset : ", seek_offset)
		
		try: 		
			with open(weight_file2, "rb") as weight:
#				print("In the loop")
				data2 = weight.read()
				weight_bin.seek(seek_offset)
				weight_bin.write(data2)
		except:
			print("	Skipping file ", weight_file2)

	

#	lines = map_file.readlines()
#	for line in lines:
#		split = line.find('@')
#		weight_file = line[:split]
#		print("weight file : ", weight_file)
#		addr = int(line[split+3:], 16)
#		print("addr : ", addr)
#		seek_offset = addr - base_addr
#		print("seek offset : ", seek_offset)
#		with open(weight_file, "rb") as weight:
#			data = weight.read()
#			weight_bin.seek(seek_offset)
#			weight_bin.write(data)

	map_file.close()
	weight_bin.close

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('-m', help="param json(ex> param.json)")
    parser.add_argument('-p', help="parameter path(ex> nmp_param_xxx.bin)")
    args = parser.parse_args()
    main(args.m, args.p)
