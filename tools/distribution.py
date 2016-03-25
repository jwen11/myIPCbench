import os,sys

out  =open(sys.argv[1] + '.dist', 'w')
fi = sys.argv[1]
latency = []

log = open(fi,'r')
#discard first 5 lines
for x in range (0,5):
	line = log.readline()

line = log.readline()
while line :
	word = line.split()
	latency.append(int(word[1]))
	line = log.readline()


for i in range (0, int(max(latency) +1 )):
	out.write(`i` + ': ' + `latency.count(i) ` + '\n')
out.close()
	
