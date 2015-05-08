#include <iostream>
extern"C" {
  void init_(int *n, int** alive);
}

extern"C" {
  void print_(int *n, int** alive);
}

int main() {  
  int n;
  int *alive;

  std::cout << "calling init" << std::endl; 
  init_(&n,&alive);
  std::cout << "n=" << n << std::endl;
  std::cout << "calling print" << std::endl;
  print_(&n,&alive);
  return 0;
}
