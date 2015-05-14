gfortran -c global.f95
g++ -c main.cpp
g++ -o main global.o main.o -lgfortran
