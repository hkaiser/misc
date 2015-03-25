gfortran -c kernel.f95
g++ -c main.cpp -L/home/zbyerly/research/hpx/ -I/home/zbyerly/research/hpx -lhpx
g++ -o main kernel.o main.o -lgfortran
