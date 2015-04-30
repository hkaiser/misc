#include "read_input.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

//Reads data from the fort.15 file
values read_input(
		  std::ifstream& fort15file,
		  std::ifstream& fort14file
		)
{
  values values_here;

  std::string buffer(1024, ' ');

  //read RUNDES  string, 30 characters
  std::getline(fort15file, values_here.RUNDES);
  values_here.RUNDES.resize(30); //resize to 30 characters
  //read RUNID   string, 20 characters
  std::getline(fort15file, values_here.RUNID);
  values_here.RUNID.resize(20); //resize to 20 characters
  //read NFOVER  int
  fort15file >> values_here.NFOVER;
  std::getline(fort15file, buffer);
  //read NABOUT
  fort15file >> values_here.NABOUT;
  std::getline(fort15file, buffer);
  //read NSCREEN
  fort15file >> values_here.NSCREEN;
  std::getline(fort15file, buffer);

  //NSCREEN_INC = NSCREEN 

  //read IHOT
  fort15file >> values_here.IHOT;
  std::getline(fort15file, buffer);
  //read ICS
  fort15file >> values_here.IHOT;
  std::getline(fort15file, buffer);
  //read IM
  fort15file >> values_here.IM;
  std::getline(fort15file, buffer);
  if (values_here.IM==0) {
    values_here.C2DDI = true;
  } else {
    throw std::runtime_error("IM != 0 not currently supported.");	 
  }

  //read NOLIBF
  fort15file >> values_here.NOLIBF;
  std::getline(fort15file, buffer);
  if (values_here.NOLIBF != 1) {
    throw std::runtime_error("NOLIBF != 1 not currently supported.");
  }
  //read NOLIFA
  fort15file >> values_here.NOLIFA;
  std::getline(fort15file, buffer);

  //NSTARTDRY = 0

  //read NOLICA
  fort15file >> values_here.NOLICA;
  std::getline(fort15file, buffer);
  //read NOLICAT
  fort15file >> values_here.NOLICAT;
  std::getline(fort15file, buffer);
  //read NWP
  fort15file >> values_here.NWP;
  std::getline(fort15file, buffer);

  // CALL ReadNodalAttr( ... )

  //read NCOR
  fort15file >> values_here.NCOR;
  std::getline(fort15file, buffer);
  if (values_here.NCOR != 0) {
      throw std::runtime_error("NCOR != 0 not currently supported.");
  }

  //read NTIP
  fort15file >> values_here.NTIP;
  std::getline(fort15file, buffer);
  //read NWS
  fort15file >> values_here.NWS;
  std::getline(fort15file, buffer);
  if (values_here.NWS != 0) {
      throw std::runtime_error("NWS != 0 not currently supported.");
  }
  // NRS=0, FRW=0

  //read NRAMP
  fort15file >> values_here.NRAMP;
  std::getline(fort15file, buffer);
  if ( (values_here.NRAMP != 0) && (values_here.NRAMP != 0) ) {
      throw std::runtime_error("NRAMP != 0 or 1 not currently supported.");
  }

  //read G      double
  fort15file >> values_here.G;
  std::getline(fort15file, buffer);
  //read TAU0   double
  fort15file >> values_here.TAU0;
  std::getline(fort15file, buffer);
  //read DT   double
  fort15file >> values_here.DTDP;
  std::getline(fort15file, buffer);
  values_here.DT = values_here.DTDP; //this was in read_input.F
  //read STATIM double
  fort15file >> values_here.STATIM;
  std::getline(fort15file, buffer);
  //read REFTIM  double
  fort15file >> values_here.REFTIM;
  std::getline(fort15file, buffer);
  
  
  //read RNDAY  double
  fort15file >> values_here.RNDAY;
  std::getline(fort15file, buffer);
  // NT = INT(RNDAY*(86400.0/DTDP) + 0.5)
  // FluxSettlingTime = 0.0
  // Dramp = 1.0  //default value for dramp?

  //read DRAMP
  fort15file >> values_here.DRAMP;
  std::getline(fort15file, buffer);
  
  //IRAMPING = INT(DRAMP*(86400.0/DTDP)+0.5)

  //read time weighting factors
  fort15file >> values_here.A00;
  fort15file >> values_here.B00;
  fort15file >> values_here.C00;
  std::getline(fort15file, buffer);

  //read H0
  if (values_here.NOLIFA == 2) {
      throw std::runtime_error("NOLIFA == 2 not currently supported.");
  }
  fort15file >> values_here.H0;
  std::getline(fort15file, buffer);

  //read SLAM0, SFEA0
  fort15file >> values_here.SLAM0;
  fort15file >> values_here.SFEA0;
  std::getline(fort15file, buffer);
  //TODO: fix this
  //values_here.SLAM0 = values_here.SLAM0*DEG2RAD;
  //values_here.SFEA0 = values_here.SFEA0*DEG2RAD;

  // At line 1237 in read_input.F, we need grid information
  // from fort.14 and ALLOC_MAIN1 is called. 

  // continue reading from the fort.15 file
  // read CF
  fort15file >> values_here.CF;
  std::getline(fort15file, buffer);

  // read ESLM
  fort15file >> values_here.ESLM;
  std::getline(fort15file, buffer);

  // read CORI
  fort15file >> values_here.CORI;
  std::getline(fort15file, buffer);

  // TODO:
  // has to be done where we know NP
  // DO I=1,NP
  //   CORIF(I) = CORI
  // ENDDO

  // read NTIF (also called NTIP??) askclint
  fort15file >> values_here.NTIF;
  std::getline(fort15file, buffer);  
  if (values_here.NTIF != 0 ) {
      throw std::runtime_error("NTIF != 0 not currently supported.");
  }  

  // call alloc_main4a()

  // call alloc_main4b()

  // read NBFR 
  fort15file >> values_here.NBFR;
  std::getline(fort15file, buffer);  
  if (values_here.NBFR != 0 ) {
      throw std::runtime_error("NBFR != 0 not currently supported.");
  }  
  // IF (NBFR == 0) MNBFR = 1

  // read ANGINN
  fort15file >> values_here.ANGINN;
  std::getline(fort15file, buffer);  
  // COSTSET=COS(ANGINN*DEG2RAD)

  // read NFFR
  fort15file >> values_here.NFFR;
  std::getline(fort15file, buffer);  
  // MNFFR = NFFR
  // IF (NFFR == 0) MNFFR = 1   askclint  

  // call alloc_main6()

  //TODO somewhere else:
  // DO I=1, NVELME
  //   J=ME2GW(I)
  //   QNAM(1,J)=0.0
  //   QNPH(1,J)=0.0
  // ENDDO

  

  return values_here;
};
