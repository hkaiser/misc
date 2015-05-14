#include <iostream>

extern"C" {
  void init_fort_(int *n, int** global);
}

extern"C" {
  void print_fort_(int** global);
}

int main() {  
  int n;
  int *global = NULL; // global is not really an int!

  std::cout << "initializing alive" << std::endl;
  
  n = 10;
  init_fort_(&n,&global);  

  std::cout << "printing" << std::endl;
  print_fort_(&global);

  return 0;
}
