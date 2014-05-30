#!/usr/bin/env python

#
# Python-based NetCDF ADCIRC data level comparison tool.
#
# Copyright Zach Byerly 2014.
# Distributed under the Boost Software License, Version 1.0.
# (See http://www.boost.org/LICENSE_1_0.txt)
#
# see netcdf_demo.py for example stuff

import sys
from subprocess import call
from Scientific.N import *
from Scientific.IO.NetCDF import *
import time

if (len(sys.argv) != 4):
    print "Usage: "+str(sys.argv[0])+" infile1.nc infile2.nc outfile.nc"
    exit()

file1_name=str(sys.argv[1])
file2_name=str(sys.argv[2])
outfile_name=str(sys.argv[3])

#Copy the first file to the outfile
call(["nccopy",file1_name,outfile_name])


#Read in input files
file1 = NetCDFFile(file1_name, 'r')
file2 = NetCDFFile(file2_name, 'r')

outfile = NetCDFFile(outfile_name, 'w')

#outfile = file1 # Can I do this? No.

if (file1.dimensions != file2.dimensions):
    print "WARNING: "+file1_name+" dimensions do not match "+file2_name+" dimensions."
    print file1.dimensions
    print file2.dimensions


time1 = file1.variables['time']
time2 = file1.variables['time']

time1_units = time1.units
time2_units = time2.units

if (time1_units != time2_units):
    print "WARNING: "+file1_name+" time units do not match "+file2_name+" time units."
    print time1_units
    print time2_units

zeta1 = file1.variables['zeta']
zeta2 = file2.variables['zeta']

zeta_output = zeta1

print file1.dimensions

if (zeta1 != zeta2):
    print "WARNING: zeta from "+file1_name+" does not match zeta from "+file1_name+"."
    print time1
#    for j in range(int(file1.dimensions['time'])):
#        print j
#        zeta_output[j,:] = zeta1[j,:]-zeta2[j,:]
#        for i in range(file1.dimensions['node']):
#            print zeta1[0,i]
            

file1.close()
file2.close()
outfile.close()
