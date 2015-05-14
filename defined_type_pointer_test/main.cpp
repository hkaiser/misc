
#include <iostream>
#include "fname.h"

extern"C" {
  void FNAME(init_fort)(int *n, void** global);
  void FNAME(print_fort)(void** global);
  void FNAME(term_fort)(void** global);
}

int main() {
  int n = 10;
  void *global = NULL;

  std::cout << "initializing alive" << std::endl;
  FNAME(init_fort)(&n,&global);

  std::cout << "printing" << std::endl;
  FNAME(print_fort)(&global);

  FNAME(term_fort)(&global);

  return 0;
}
