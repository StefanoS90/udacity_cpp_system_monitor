#include <string>
#include <cmath>
#include "format.h"
#include <iostream>

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) 
{ 
  int hours   = std::floor(seconds/3600.0);
  int minutes = std::floor((seconds % 3600)/60);
  int sec = std::floor(seconds % 60);
  string out_string = std::to_string(hours) + ":" + std::to_string(minutes) + ":" + std::to_string(sec);
  return out_string; 
  
}