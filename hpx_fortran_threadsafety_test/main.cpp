#include <iostream>

#include <hpx/hpx.hpp>
#include <hpx/hpx_start.hpp>
#include <hpx/hpx_init.hpp>
#include <hpx/include/actions.hpp>
#include <hpx/include/components.hpp>
#include <hpx/include/async.hpp>
#include <hpx/include/util.hpp>

#define N_MAX 20
#define MAX_NEIGHBORS 20

extern"C" {
  int kernel_(int *n,
	      double alive[N_MAX],
	      int numneighbors[N_MAX],
	      int neighbors[N_MAX][MAX_NEIGHBORS]
	      );
}

struct subdomain
{
  int n;
  double alive[N_MAX];
  int numneighbors[N_MAX];
  int neighbors[N_MAX][MAX_NEIGHBORS];
  int any_alive;

  template <class ARCHIVE>
  void serialize(ARCHIVE& ar, unsigned)
  {
    ar & n & alive & numneighbors & neighbors & any_alive;
  }

};

int kernel(subdomain subd)
{
  return kernel_(& subd.n, subd.alive, subd.numneighbors, subd.neighbors);
}

HPX_PLAIN_ACTION(kernel, kernel_action)

void subd_init(subdomain *subd) {
  std::cout << "Initializing subdomain" << std::endl;
  std::cout << "subd->n = " << subd->n << std::endl;
  for (int i=0; i<subd->n; i++) {    
    subd->alive[i] = 0.0;
    std::cout << "subd->alive[i] " << subd->alive[i] << std::endl;
    subd->numneighbors[i] = 2;
    subd->neighbors[i][0] = i-1;
    subd->neighbors[i][1] = i+1;
  }
  //Periodic Boundary
  subd->neighbors[0][0] = subd->n-1;
  subd->neighbors[subd->n-1][1] = 0;
}  

int hpx_main(
	 int argc
	 , char** argv
	 )
{

  // Initialize 4 subdomains
  subdomain sub1;
  sub1.n = 10;
  subd_init(&sub1);

  subdomain sub2;
  sub2.n = 8;
  subd_init(&sub2);

  subdomain sub3;
  sub3.n = 7;
  subd_init(&sub3);

  subdomain sub4;
  sub4.n = 5;
  subd_init(&sub4);
  
  // Seed single alive cell
  sub1.alive[2] = 1.0;

  /*
  // Debugging output
  std::cout << "sub2.n = " << sub2.n << std::endl;
  for (int i=0; i< sub2.n; i++) {
    std::cout << "sub2.alive[" << i << "] = " << sub2.alive[i] << std::endl;
    std::cout << "sub2.numneighbors[" << i << "] = " << sub2.numneighbors[i] << std::endl;
  }
  */

  hpx::future<int> sum1 = hpx::async<kernel_action>(hpx::find_here(), sub1);
  hpx::future<int> sum2 = hpx::async<kernel_action>(hpx::find_here(), sub2);
  hpx::future<int> sum3 = hpx::async<kernel_action>(hpx::find_here(), sub3);
  hpx::future<int> sum4 = hpx::async<kernel_action>(hpx::find_here(), sub4);

  std::cout << "alive1 = " << sum1.get() << std::endl;
  std::cout << "alive2 = " << sum2.get() << std::endl;
  std::cout << "alive3 = " << sum3.get() << std::endl;
  std::cout << "alive4 = " << sum4.get() << std::endl;

  //std::cout << "cpp: n=" << n << std::endl;

  /*
    for (int timestep=0; timestep<10; timestep++) {
    std::cout << "**** timestep = " << timestep << std::endl;
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
  hpx::init(argc,argv);
 
  return 0;
}
