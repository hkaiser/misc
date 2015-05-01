#include "fort80reader.h"
#include "file_opener.h"
#include "read_input.h"
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

    double RHOWAT0 = 1000.0; //from line 203 in read_input.F askclint

    // Read data from files
    values values_here = read_input(fort15file, fort14file);
    
    // Read MNP and MNE from fort.14 file,
    // then duplicate ALLOC_MAIN1() here   askclint about alloc_main1

    // call a read fort.14 subroutine here. start on line 1242 of read_input.F
    // CALL INVCP , just a coord transform

    if (domainID == 0) {
      std::cout << "dgswe     = " << fortdgvalues_here.dgswe   << std::endl;
      std::cout << "dgswe     = " << fortdgvalues_here.dgswe     << std::endl;
      std::cout << "dg_to_cg  = " << fortdgvalues_here.dg_to_cg  << std::endl;
      std::cout << "modal_ic  = " << fortdgvalues_here.modal_ic  << std::endl;
      std::cout << "padapt    = " << fortdgvalues_here.padapt    << std::endl;
      std::cout << "pflag     = " << fortdgvalues_here.pflag     << std::endl;
      std::cout << "gflag     = " << fortdgvalues_here.gflag     << std::endl;
      std::cout << "dis_tol   = " << fortdgvalues_here.dis_tol   << std::endl;
      std::cout << "pl        = " << fortdgvalues_here.pl        << std::endl;
      std::cout << "ph        = " << fortdgvalues_here.ph        << std::endl;
      std::cout << "px        = " << fortdgvalues_here.px        << std::endl;
      std::cout << "slimit    = " << fortdgvalues_here.slimit    << std::endl;
      std::cout << "plimit    = " << fortdgvalues_here.plimit    << std::endl;
      std::cout << "k         = " << fortdgvalues_here.k         << std::endl;
      std::cout << "ks        = " << fortdgvalues_here.ks        << std::endl;
      std::cout << "L         = " << fortdgvalues_here.L         << std::endl;
      std::cout << "nelem     = " << fortdgvalues_here.nelem     << std::endl;
      std::cout << "fluxtype  = " << fortdgvalues_here.fluxtype  << std::endl;
      std::cout << "rk_stage  = " << fortdgvalues_here.rk_stage  << std::endl;
      std::cout << "rk_order  = " << fortdgvalues_here.rk_order  << std::endl;
      std::cout << "slopeflag = " << fortdgvalues_here.slopeflag << std::endl;
      std::cout << "weight    = " << fortdgvalues_here.weight    << std::endl;
      std::cout << "sedflag   = " << fortdgvalues_here.sedflag   << std::endl;
      
      std::cout << "RUNDES    = " << values_here.RUNDES    << std::endl;
      std::cout << "RUNID     = " << values_here.RUNID     << std::endl;
      std::cout << "NFOVER    = " << values_here.NFOVER    << std::endl;
      std::cout << "NABOUT    = " << values_here.NABOUT    << std::endl;
      std::cout << "NSCREEN   = " << values_here.NSCREEN   << std::endl;
      std::cout << "IHOT      = " << values_here.IHOT      << std::endl;
      std::cout << "ICS       = " << values_here.ICS       << std::endl;
      std::cout << "IM        = " << values_here.IM        << std::endl;
      std::cout << "NOLIBF    = " << values_here.NOLIBF    << std::endl;
      std::cout << "NOLIFA    = " << values_here.NOLIFA    << std::endl;
      std::cout << "NOLICA    = " << values_here.NOLICA    << std::endl;
      std::cout << "NOLICAT   = " << values_here.NOLICAT   << std::endl;
      std::cout << "NWP       = " << values_here.NWP       << std::endl;
      std::cout << "NCOR      = " << values_here.NCOR      << std::endl;
      std::cout << "NTIP      = " << values_here.NTIP      << std::endl;
      std::cout << "NWS       = " << values_here.NWS       << std::endl;
      std::cout << "NRAMP     = " << values_here.NRAMP     << std::endl;
      std::cout << "G         = " << values_here.G         << std::endl;
      std::cout << "TAU0      = " << values_here.TAU0      << std::endl;
      std::cout << "DTDP      = " << values_here.DTDP      << std::endl;
      std::cout << "DT        = " << values_here.DT        << std::endl;
      std::cout << "STATIM    = " << values_here.STATIM    << std::endl;
      std::cout << "REFTIM    = " << values_here.REFTIM    << std::endl;
    }    

  }

}
