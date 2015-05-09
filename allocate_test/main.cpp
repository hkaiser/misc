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
  init_(&n,&alive);
  std::cout << "n=" << n << std::endl;
  print_(&n,&alive);
  return 0;
}
