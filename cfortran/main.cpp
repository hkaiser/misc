//#define MAX 100
#include <iostream>

extern "C"{
  void avgdepth_(int *numnodes, float depth[], float *avg);
}

int main()
{
  int numnodes = 5;
  float depth[numnodes] = {1.0, 2.0, 3.0, 4.0, 5.0};

  float avg = 0.0;

  avgdepth_(&numnodes, depth, &avg);

  std::cout << "average depth = " << avg << std::endl;

}
