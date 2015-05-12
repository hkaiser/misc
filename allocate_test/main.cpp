#include <iostream>
#include <vector>
extern"C" {
  void init_(int *n, double** alive);
}

extern"C" {
  void print_(int *n, double** alive);
}

int main() {  
  int n;
  double *alive = 0;
  double *alive2 = 0;
  //double *alive3;


  std::cout << "initializing alive" << std::endl;
  
  //n = 10;
  //  std::vector<double> alive(n);
  //alive.data();

  init_(&n,&alive);
  //  init_(&n,&alive3);

  alive2 = alive;


  //  std::cout << "initializing alive2" << std::endl;
  //  init_(&n,&alive2);

  std::cout << "printing alive" << std::endl;
  print_(&n,&alive);

  std::cout << "printing alive2" << std::endl;
  print_(&n,&alive2);

  return 0;
}
