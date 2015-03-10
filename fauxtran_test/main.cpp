#include <iostream>
#include "kernel.cpp"

#define N 5

int main() {

  int alive[N];
  int numneighbors[N];
  int neighbors[20][N];
  
  for (int i=0; i<N; i++) {
    alive[i] = 0;
    numneighbors[i] = 2;
    neighbors[0][i] = i-1;
    neighbors[1][i] = i+1;
  }
  
  alive[0]=1;
  
  neighbors[0][0] = N;
  neighbors[1][N] = 0;

  KERNEL(N,alive,numneighbors,neighbors);
  KERNEL(N,alive,numneighbors,neighbors);

  for (int i=0; i<N; i++) {
    std::cout << alive[i] << "\n";
  }
  

}
