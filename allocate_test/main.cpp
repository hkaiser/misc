#include <iostream>
extern"C" {
  void init_(int *n, double** alive);
}

extern"C" {
  void print_(int *n, double** alive);
}

int main() {  
  int n;
  double *alive;
  double *alive2;


  std::cout << "initializing alive" << std::endl;
  init_(&n,&alive);

  std::cout << "initializing alive2" << std::endl;
  init_(&n,&alive2);

  std::cout << "printing alive" << std::endl;
  print_(&n,&alive);

  std::cout << "printing alive2" << std::endl;
  print_(&n,&alive2);

  return 0;
}
