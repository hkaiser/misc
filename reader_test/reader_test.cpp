#include "fort80reader.h"
#include "file_opener.h"
#include "fort15reader.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

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
  file_opener(fort80filename, fort80file);
  readfort80(fort80file, &numberOfDomains, &numberOfElements, &numberOfPoints);

  std::cout << "Number of domains:" << numberOfDomains << std::endl;
  std::cout << "Number of elements:" << numberOfElements << std::endl;
  std::cout << "Number of points:" << numberOfPoints << std::endl;


  // Read domain specific input files (DG.18, fort.14, fort.15, fort.18, fort.dg)
  for (int i=0; i<numberOfDomains; i++) {

    // Generate filenames for this domain
    int domainID=i;
    std::stringstream buf;
    buf.width(4);
    buf.fill('0');
    buf << domainID;
    std::string filename = meshDir;
    filename.append("/PE");
    filename.append(buf.str());
    std::string fort14filename = filename;
    std::string fort15filename = filename;
    std::string fortdgfilename = filename;
    std::string DG18filename = filename;
    fort14filename.append("/fort.14");
    fort15filename.append("/fort.15");
    fortdgfilename.append("/fort.dg");
    DG18filename.append("/DG.18");
    

    // Open Files for reading
    std::ifstream fort15file;    
    std::ifstream fort14file;
    std::ifstream fortdgfile;
    std::ifstream DG18file;
    file_opener(fort15filename, fort15file);
    file_opener(fort14filename, fort14file);
    file_opener(fortdgfilename, fortdgfile);
    file_opener(DG18filename, DG18file);

    // Read data from files
    fort15 fort15values_here = readfort15(fort15file);
    
    std::cout << "RUNDES = " << fort15values_here.RUNDES << std::endl;
  }

}
