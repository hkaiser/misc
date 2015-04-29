#include <iostream>
#include <fstream>
#include <vector>

std::ifstream& openfort80File(std::string fort80filename);
void readfort80(std::ifstream& fort80file, int *numberOfDomains, int *numberOfElements, int *numberOfPoints);

//, std::vector<ownerTableEntry> *ownerTable
