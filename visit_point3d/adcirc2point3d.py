#!/usr/bin/env python
import math
import sys

if (len(sys.argv) != 2):
    print "Usage: "+str(sys.argv[0])+" fort.14"
    exit()

filename=str(sys.argv[1])

infile = open(filename)

f = open("values.3D", "wt")
f.write("x y z value\n");


counter = 0
for line in infile:

#    print counter, line
    counter=counter+1

    if counter == 1:
        continue
    if counter == 2:
        np = line.split()[1]
        continue
    
    nodeID = line.split()[0]
    x = float(line.split()[1])
    y = float(line.split()[2])
    depth = float(line.split()[3])
    value = 0.0

#    print x, y, depth
    f.write("%g %g %g %g\n" % (x,y,depth,value))


    if nodeID == np:
        break


infile.close()
f.close()
