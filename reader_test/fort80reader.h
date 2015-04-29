#include <iostream>
#include <fstream>
#include <vector>

void openfort80File(std::string fort80filename, std::ifstream& fort80file);
void readfort80(std::ifstream& fort80file, int *numberOfDomains, int *numberOfElements, int *numberOfPoints);

//, std::vector<ownerTableEntry> *ownerTable
