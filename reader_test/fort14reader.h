#include <iostream>
#include <fstream>
#include <vector>

void readFort14Header(std::ifstream& fort14file, int *numberOfElements, int *numberOfPoints);
void readFort14Points(std::ifstream& fort14file, std::vector<FloatCoord<3> > *points, std::vector<int> *localIDs, const int numberOfPoints);
