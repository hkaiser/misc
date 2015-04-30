#include "fort80reader.h"
#include "file_opener.h"
#include "fort15reader.h"
#include "fortdgreader.h"
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

    fortdg fortdgvalues_here = readfortdg(fortdgfile);

    // Read data from files
    fort15 fort15values_here = readfort15(fort15file);
    
    if (false) {
      std::cout << 

      std::cout << "RUNDES  = " << fort15values_here.RUNDES  << std::endl;
      std::cout << "RUNID   = " << fort15values_here.RUNID   << std::endl;
      std::cout << "NFOVER  = " << fort15values_here.NFOVER  << std::endl;
      std::cout << "NABOUT  = " << fort15values_here.NABOUT  << std::endl;
      std::cout << "NSCREEN = " << fort15values_here.NSCREEN << std::endl;
      std::cout << "IHOT    = " << fort15values_here.IHOT    << std::endl;
      std::cout << "ICS     = " << fort15values_here.ICS     << std::endl;
      std::cout << "IM      = " << fort15values_here.IM      << std::endl;
      std::cout << "NOLIBF  = " << fort15values_here.NOLIBF  << std::endl;
      std::cout << "NOLIFA  = " << fort15values_here.NOLIFA  << std::endl;
      std::cout << "NOLICA  = " << fort15values_here.NOLICA  << std::endl;
      std::cout << "NOLICAT = " << fort15values_here.NOLICAT << std::endl;
      std::cout << "NWP     = " << fort15values_here.NWP     << std::endl;
      std::cout << "NCOR    = " << fort15values_here.NCOR    << std::endl;
      std::cout << "NTIP    = " << fort15values_here.NTIP    << std::endl;
      std::cout << "NWS     = " << fort15values_here.NWS     << std::endl;
      std::cout << "NRAMP   = " << fort15values_here.NRAMP   << std::endl;
      std::cout << "G       = " << fort15values_here.G       << std::endl;
      std::cout << "TAU0    = " << fort15values_here.TAU0    << std::endl;
      std::cout << "DTDP    = " << fort15values_here.DTDP    << std::endl;
      std::cout << "DT      = " << fort15values_here.DT      << std::endl;
      std::cout << "STATIM  = " << fort15values_here.STATIM  << std::endl;
      std::cout << "REFTIM  = " << fort15values_here.REFTIM  << std::endl;
    }    

  }

}
