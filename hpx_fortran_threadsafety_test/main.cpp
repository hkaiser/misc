#include <iostream>

#include <hpx/hpx.hpp>
#include <hpx/hpx_start.hpp>
#include <hpx/hpx_init.hpp>
#include <hpx/include/actions.hpp>
#include <hpx/include/components.hpp>
#include <hpx/include/async.hpp>
#include <hpx/include/util.hpp>

/*
#define N_MAX 20
#define MAX_NEIGHBORS 20
*/

extern"C" {
  void kernel_();
}

/*
extern"C" {
  extern struct{
    int n;
    int alive[N_MAX];
    int numneighbors[N_MAX];
    int neighbors[MAX_NEIGHBORS][N_MAX];    
  } variables_;
}
*/

//Stripped down version of the common block
extern"C" {
  extern struct{
    int n;
  } variables_;
}

int kernel(int n)
{
  variables_.n = n;
  kernel_();
}


HPX_PLAIN_ACTION(kernel, kernel_action)


int hpx_main(
	 int argc
	 , char** argv
	 )
{

  int n=10;
  int timesteps = 10;

  int sum = hpx::async<kernel_action>(hpx::find_here(), n).get();

  std::cout << "timesteps = " << timesteps << std::endl;

  /*
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
 
  */
  return hpx::finalize();
}

int main(
	 int argc
	 , char* argv[]
	 )
{
  // Initialize and run HPX
  hpx::start(argc, argv);

  hpx::stop;
 
  return 0;
}
