#include "file_opener.h"
#include <iostream>
#include <stdexcept>

void file_opener(std::string filename, std::ifstream& file)
{
  file.open(filename.c_str());
  if (!file) {
    throw std::runtime_error("could not open file "+filename);
  }
}
