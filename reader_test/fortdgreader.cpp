#include "fortdgreader.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <string>

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
    //std::cout << "key is:" << key << ", value is:" << value << "," << std::endl;
    
    //TODO: make this more robust, add error handling, etc.

    if (key == "dgswe")     fortdg_here.dgswe     = std::stoi(value);
    if (key == "dg_to_cg")  fortdg_here.dg_to_cg  = std::stoi(value);
    if (key == "modal_ic")  fortdg_here.modal_ic  = std::stoi(value);
    if (key == "padapt")    fortdg_here.padapt    = std::stoi(value);
    if (key == "pflag")     fortdg_here.pflag     = std::stoi(value);
    if (key == "gflag")     fortdg_here.gflag     = std::stoi(value);
    if (key == "dis_tol")   fortdg_here.dis_tol   = std::stoi(value);
    if (key == "pl")        fortdg_here.pl        = std::stoi(value);
    if (key == "ph")        fortdg_here.ph        = std::stoi(value);
    if (key == "px")        fortdg_here.px        = std::stoi(value);
    if (key == "slimit")    fortdg_here.slimit    = std::stod(value);
    if (key == "plimit")    fortdg_here.plimit    = std::stoi(value);
    if (key == "k")         fortdg_here.k         = std::stoi(value);
    if (key == "ks")        fortdg_here.ks        = std::stod(value);
    if (key == "L")         fortdg_here.L         = std::stoi(value);
    if (key == "nelem")     fortdg_here.nelem     = std::stoi(value);
    if (key == "fluxtype")  fortdg_here.fluxtype  = std::stoi(value);
    if (key == "rk_stage")  fortdg_here.rk_stage  = std::stoi(value);
    if (key == "rk_order")  fortdg_here.rk_order  = std::stoi(value);
    if (key == "slopeflag") fortdg_here.slopeflag = std::stoi(value);
    if (key == "weight")    fortdg_here.weight    = std::stoi(value);
    if (key == "sedflag")   fortdg_here.sedflag   = std::stoi(value);
  }
  return fortdg_here;
};
