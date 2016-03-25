import os
import sys

index =0
os.chdir(sys.argv[1])
filename = os.listdir('.')
filename.sort()
print filename 
for fi in filename:
	os.rename(fi, 'corun'+ `index`+ '.log')
	index = index +1
print 'rename finished'
