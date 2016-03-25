import os,sys

out  =open(sys.argv[1] + '.result', 'w')
out.write('filename\tmaxLat\tavgLat\tmedianLat\t99PLat')
os.chdir(sys.argv[1])
filename = os.listdir('.')
filename.sort()
for fi in filename:
	log = open(fi,'r')
	line = log.readline()
	out.write('\n')
	out.write(fi + '\t')
	for x in range (0,4):
		line = log.readline()
		word = line.split()
		if word[3] == 'is': 
			out.write(word[4] + '\t')
		if word[4] == 'is': 
			out.write(word[5] + '\t')

