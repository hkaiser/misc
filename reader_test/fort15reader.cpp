#include "fort15reader.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

//Reads data from the fort.15 file
fort15 readfort15(
		std::ifstream& fort15file
		)
{
  fort15 fort15_here;

  std::string buffer(1024, ' ');

  //read RUNDES  string, 30 characters
  std::getline(fort15file, fort15_here.RUNDES);
  fort15_here.RUNDES.resize(30); //resize to 30 characters
  //read RUNID   string, 20 characters
  std::getline(fort15file, fort15_here.RUNID);
  fort15_here.RUNID.resize(20); //resize to 20 characters
  //read NFOVER  int
  fort15file >> fort15_here.NFOVER;
  std::getline(fort15file, buffer);
  //read NABOUT
  fort15file >> fort15_here.NABOUT;
  std::getline(fort15file, buffer);
  //read NSCREEN
  fort15file >> fort15_here.NSCREEN;
  std::getline(fort15file, buffer);
  //read IHOT
  fort15file >> fort15_here.IHOT;
  std::getline(fort15file, buffer);
  //read ICS
  fort15file >> fort15_here.IHOT;
  std::getline(fort15file, buffer);
  //read IM
  fort15file >> fort15_here.IM;
  std::getline(fort15file, buffer);
  //read NOLIBF
  fort15file >> fort15_here.NOLIBF;
  std::getline(fort15file, buffer);
  //read NOLIFA
  fort15file >> fort15_here.NOLIFA;
  std::getline(fort15file, buffer);
  //read NOLICA
  fort15file >> fort15_here.NOLICA;
  std::getline(fort15file, buffer);
  //read NOLICAT
  fort15file >> fort15_here.NOLICAT;
  std::getline(fort15file, buffer);
  //read NWP
  fort15file >> fort15_here.NWP;
  std::getline(fort15file, buffer);
  //read NCOR
  fort15file >> fort15_here.NCOR;
  std::getline(fort15file, buffer);
  //read NTIP
  fort15file >> fort15_here.NTIP;
  std::getline(fort15file, buffer);
  //read NWS
  fort15file >> fort15_here.NWS;
  std::getline(fort15file, buffer);
  //read NRAMP
  fort15file >> fort15_here.NRAMP;
  std::getline(fort15file, buffer);
  //read G      double
  fort15file >> fort15_here.G;
  std::getline(fort15file, buffer);
  //read TAU0   double
  fort15file >> fort15_here.TAU0;
  std::getline(fort15file, buffer);
  //read DT   double
  fort15file >> fort15_here.DTDP;
  std::getline(fort15file, buffer);
  fort15_here.DT = fort15_here.DTDP; //this was in read_input.F
  //read STATIM double
  fort15file >> fort15_here.STATIM;
  std::getline(fort15file, buffer);
  //read REFTIM  double
  fort15file >> fort15_here.REFTIM;
  std::getline(fort15file, buffer);
  
  // Now it gets complicated.
  if (fort15_here.NWS != 0) 
    {
      throw std::runtime_error("NWS != 0 not currently supported.");
    }
  
  //read RNDAY

  return fort15_here;
};
