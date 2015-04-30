#include "fortdgreader.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>

//Reads data from the fort.dg file
fortdg readfortdg(
		std::ifstream& fortdgfile
		)
{
  fortdg fortdg_here;

  std::string buffer(1024, ' ');
  std::string comment = "!";
  std::string delimiter = " = ";

  //read dgswe

  while (!fortdgfile.eof()) {
    std::getline(fortdgfile, buffer);
    //remove everything after first comment character
    std::string key_val_pair = buffer.substr(0, buffer.find_first_of(comment));

    //remove all spaces
    key_val_pair.erase(
		       std::remove(key_val_pair.begin(), 
				   key_val_pair.end(), 
				   ' ')
		       , key_val_pair.end()
		       );
    // if nothing is left, skip to the next line
    if (key_val_pair.empty()) continue;
    int pos = buffer.find_first_of(delimiter); // position of the delimiter
    std::string key   = key_val_pair.substr(0, pos);
    std::string value = key_val_pair.substr(pos+1);
    
    //std::cout << "key_val_pair is:" << key_val_pair << "," <<std::endl;
    std::cout << "key is:" << key << ", value is:" << value << "," << std::endl;

  }
  return fortdg_here;
};
