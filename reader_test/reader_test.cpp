#include "fort80reader.h"
#include <iostream>
#include <fstream>
#include <vector>

int main(int argc, char *argv[])
{
  std::string meshDir = ".";
  
  // Declare variables we want from the fort.80 file
  int numberOfDomains;
  int numberOfElements;
  int numberOfPoints;

  // Read in fort.80 file
  std::string fort80filename = meshDir;
  fort80filename.append("/fort.80");
  std::ifstream fort80file;
  openfort80File(fort80filename, fort80file);
  readfort80(fort80file, &numberOfDomains, &numberOfElements, &numberOfPoints);

  std::cout << "Number of domains:" << numberOfDomains << std::endl;
  std::cout << "Number of elements:" << numberOfElements << std::endl;
  std::cout << "Number of points:" << numberOfPoints << std::endl;

}
