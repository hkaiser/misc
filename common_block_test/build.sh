gfortran -c kernel.f95
g++ -c main.cpp
g++ -o main kernel.o main.o -lgfortran
