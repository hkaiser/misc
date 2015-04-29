#include "prep_DG.h"
#include "fort80reader.h"
#include "fort14reader.h"
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


  // Read domain specific input files (DG.18, fort.14, fort.15, fort.18, fort.dg)
  for (i=0; i<numberOfDomains; i++) {

    //Generate filename for fort.14 for this domain
    domainID=i;
    std::string fort14filename = meshDir;
    fort14filename.append("/PE");
    std::stringstream buf;
    buf.width(4);
    buf.fill('0');
    buf << domainID;
    fort14filename.append(buf.str());
    fort14filename.append("/fort.14");
    
    std::ifstream fort14file;
    openfort14File(fort14filename, fort14file);
  }

}
