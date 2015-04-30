#include "fort80reader.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

// Reads data from the fort.80 file
void readfort80(std::ifstream& fort80file, int *numberOfDomains, int *numberOfElements, int *numberOfPoints)
{
  std::string buffer(1024, ' ');
  //Discard first 3 lines:
  std::getline(fort80file, buffer);
  std::getline(fort80file, buffer);
  std::getline(fort80file, buffer);
  
  fort80file >> *numberOfElements;
  fort80file >> *numberOfPoints;
  
  //Discard rest of line
  std::getline(fort80file, buffer);
  
  fort80file >> *numberOfDomains;
}    
