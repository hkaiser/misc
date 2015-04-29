#include "fort80reader.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>

// Opens the fort.80 file for reading
void openfort80File(std::string fort80filename, std::ifstream& fort80file)
{
  fort80file.open(fort80filename.c_str());
  if (!fort80file) {
    throw std::runtime_error("could not open fort.80 file "+fort80filename);
  }
}

// Reads data from the fort.80 file
void readfort80(std::ifstream& fort80file, int *numberOfDomains, int *numberOfElements, int *numberOfPoints)
		//, std::vector<ownerTableEntry> *ownerTable)
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
  /*
  //Discard rest of the line:
  std::getline(fort80file, buffer);
  
  //Discard next 8 lines:
  std::getline(fort80file, buffer);
  std::getline(fort80file, buffer);
  std::getline(fort80file, buffer);
  std::getline(fort80file, buffer);
  std::getline(fort80file, buffer);
  std::getline(fort80file, buffer);
  std::getline(fort80file, buffer);
  std::getline(fort80file, buffer);

  for (int domain = 0; domain < *numberOfDomains; ++domain) {
    int buf;
    int numNodes;
    fort80file >> buf;
    if (buf != domain) {
      throw std::runtime_error("buf does not match domain");
    }
    fort80file >> numNodes;
    //Discard rest of the line
    std::getline(fort80file, buffer);
    
    for (int node = 0; node < numNodes; ++node) {
      int nodeNum;
      fort80file >> nodeNum;
    }
    
    // throw away the rest of the line
    std::getline(fort80file, buffer);
  }
  // Throw away another line
  std::getline(fort80file, buffer);
  for (int node = 0; node < *numberOfPoints; node++) {
    //    ownerTableEntry thisOwnerTableEntry;
    int global_label;
    int local_label;
    int owner;
    fort80file >> global_label;
    fort80file >> owner;
    fort80file >> local_label;
    
    //    thisOwnerTableEntry.globalID=global_label;
    //    thisOwnerTableEntry.ownerID=owner;
    //    thisOwnerTableEntry.localID=local_label;
    
    std::getline(fort80file, buffer);//discard rest of line
    
    //    ownerTable->push_back(thisOwnerTableEntry);
    */
  }            
}    
