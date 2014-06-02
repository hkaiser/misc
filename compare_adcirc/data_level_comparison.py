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

def var_subtract(var_name):
    var1 = file1.variables[var_name]
    var2 = file2.variables[var_name]

    var_output = outfile.variables[var_name]

    var_output[:,:] = var1[:,:]-var2[:,:]


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

outfile = NetCDFFile(outfile_name, 'r+')

#outfile = file1 # Can I do this? No.

if (file1.dimensions != file2.dimensions):
    print "WARNING: "+file1_name+" dimensions do not match "+file2_name+" dimensions."
    print file1.dimensions
    print file2.dimensions


time1 = file1.variables['time']
time2 = file1.variables['time']

time1_units = time1.units
time2_units = time2.units

# Check number of time steps
if (time1[:].size != time2[:].size):
    print "WARNING: "+file1_name+" number of time steps does not match "+file2_name+" number of time steps."

# Check time units
if (time1_units != time2_units):
    print "WARNING: "+file1_name+" time units do not match "+file2_name+" time units."
    print time1_units
    print time2_units

print "Variables: "
for var in file1.variables.keys():
    sys.stdout.write(var+" ")
#    vars = file1.variables[var]
#    print vars.getValue()
#    vars_array = vars[:]
#    vars_units = vars.units
#    print vars_units
print ""


var_subtract('zeta')

# Close files            
file1.close()
file2.close()
outfile.close()
