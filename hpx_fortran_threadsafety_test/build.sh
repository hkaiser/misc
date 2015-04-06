
export PKG_CONFIG_PATH=/home/zbyerly/research/scripts/hpx_install_release/lib/pkgconfig/

gfortran -c kernel.f95 -frecursive
g++ -c main.cpp `pkg-config --cflags --libs hpx_application`
g++ -o main kernel.o main.o `pkg-config --cflags --libs hpx_application` -lgfortran
