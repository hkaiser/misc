#include "fort14reader.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>

void readFort14Header(std::ifstream& fort14file, int *numberOfElements, int *numberOfPoints)
{
  std::string buffer(1024, ' ');
  // discard first line, which only holds comments anyway
  std::getline(fort14file, buffer);
  
  fort14file >> *numberOfElements;
  fort14file >> *numberOfPoints;
  
  // discard remainder of line
  std::getline(fort14file, buffer);
  
  if (!fort14file.good()) {
    throw std::logic_error("could not read header");
  }
}

void readFort14Points(std::ifstream& fort14file, std::vector<FloatCoord<3> > *points, std::vector<int> *localIDs, const int numberOfPoints)
{
  std::string buffer(1024, ' ');        
  
  for (int i = 0; i < numberOfPoints; ++i) {
    FloatCoord<3> p;
    int localID;
    
    meshFile >> localID;
    meshFile >> p[0];
    meshFile >> p[1];
    meshFile >> p[2];
    std::getline(meshFile, buffer);
    
    *points << p;
    *localIDs << localID;
  }
  
  if (!meshFile.good()) {
    throw std::runtime_error("could not read points");
  }
}




}    
