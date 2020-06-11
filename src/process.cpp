#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"
#include <iostream>

using std::string;
using std::to_string;
using std::vector;


// TODO: Return this process's ID
int Process::Pid() { return _pid; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() {  
  

  
//   std::cout << diff_active_jiffies << " " << diff_total_jiffies << std::endl;
  
  
  std::chrono::duration<double> elapsed = std::chrono::high_resolution_clock::now() - this->last_update_tick;
  if (elapsed.count()>2.0)
  {
      long jififes = LinuxParser::ActiveJiffies(this->_pid);
      long total_jiffies = LinuxParser::Jiffies();
      long diff_active_jiffies = jififes - this->prev_active_jiffies;
      long diff_total_jiffies  = total_jiffies - this->prev_total_jiffies;
      this->prev_active_jiffies = jififes;
      this->prev_total_jiffies  = total_jiffies;
      float cpu_util = 100*(float(diff_active_jiffies)/float(diff_total_jiffies));
      this->cpu_utilization = cpu_util;
      this->last_update_tick = std::chrono::high_resolution_clock::now();
  }
  
  return this->cpu_utilization;
}

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(this->_pid);}

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(this->_pid); }

// TODO: Return the user (name) that generated this process
string Process::User() { 
  return LinuxParser::User(this->_pid);
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(this->_pid); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { 
  if (this->cpu_utilization > a.cpu_utilization){return true;}
  else {return false;}
}

