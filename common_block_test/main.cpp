#include <iostream>

#define N_MAX 20
#define MAX_NEIGHBORS 20

extern"C" {
  void kernel_();
}

extern"C" {
  extern struct{
    int n;
    int alive[N_MAX];
    int numneighbors[N_MAX];
    int neighbors[MAX_NEIGHBORS][N_MAX];    
  } variables_;
}

int main() {

  int n=10;

  variables_.n = n;
  // Creating Neighbor Connectivity
  for (int i=0; i<n; i++) {
    variables_.alive[i] = 0;
    variables_.numneighbors[i] = 2;
    // This will give the neighbor IDs in the C array index style
    variables_.neighbors[i][0] = i-1;
    variables_.neighbors[i][1] = i+1;
  }

  // Creating Periodic Boundary
  variables_.neighbors[0][0] = n-1;
  variables_.neighbors[n-1][1] = 0;

  // Seeding single alive cell
  variables_.alive[0]=1;

  //std::cout << "cpp: n=" << n << std::endl;

  for (int timestep=0; timestep<10; timestep++) {
    std::cout << "**** timestep = " << timestep << std::endl;
    kernel_();
    for (int i=0; i<n; i++) {
      std::cout << "i=" << i << " alive =" << variables_.alive[i] << "\n";
    }
  }

  return 0;
}
