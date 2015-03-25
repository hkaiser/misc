#include <iostream>

extern"C" {
  void kernel_(int *n);
}

int main() {

  int n=5;

  int alive[n];
  int numneighbors[n];
  int neighbors[20][n];
  
  for (int i=0; i<n; i++) {
    alive[i] = 0;
    numneighbors[i] = 2;
    neighbors[0][i] = i-1;
    neighbors[1][i] = i+1;
  }
  
  alive[0]=1;
  
  neighbors[0][0] = n;
  neighbors[1][n] = 0;

  kernel_(&n);
  
  for (int i=0; i<n; i++) {
    std::cout << alive[i] << "\n";
  }
  

  std::cout << "Hello World!" << std::endl;

  return 0;
}
