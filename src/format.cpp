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
  
  string s = std::to_string(sec);
  s.insert(0, 2 - s.length(), '0');

  string h = std::to_string(hours);
  h.insert(0, 2 - h.length(), '0');

  string m = std::to_string(minutes);
  m.insert(0, 2 - m.length(), '0');

  
  string out_string = h + ":" + m + ":" + s;
  return out_string; 
  
}