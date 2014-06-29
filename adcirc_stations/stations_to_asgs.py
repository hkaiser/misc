#!/usr/bin/env python
print "hello world"

infile = open("in.txt")

for line in infile:
    print line.split(',')[4].rstrip(), line.split(',')[3], ' ! ',  line.split(',')[1], ' ! ', line.split(',')[2]
