#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"
#include <iostream>
#include <iostream>
#include <algorithm>


using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { 
  auto pid_list = LinuxParser::Pids();


  for (auto pid: pid_list){
      auto it = std::find_if(this->processes_.begin(), processes_.end(), [&pid](Process& proc) {return proc.Pid() == pid;});
      if (it == this->processes_.end())
      {
	// if process is not present, add it
	this->processes_.push_back(Process(pid));
      }
      else{
	// if it is present update its cpu utilization
	it->CpuUtilization();
      }
  }
  
  for (int i=0;i<this->processes_.size()-1;i++ ){
    auto process = this->processes_[i];
    auto it = std::find_if(pid_list.begin(), pid_list.end(), [&process](int& pid) {return process.Pid() == pid;});
    if (it == pid_list.end()){
      this->processes_.erase(this->processes_.begin()+i);
    }
  }
  
  std::sort(this->processes_.begin(), this->processes_.end());
  return this->processes_; }

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { return LinuxParser::Kernel(); }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

// TODO: Return the operating system name
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses();}

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// TODO: Return the number of seconds since the system started running
long int System::UpTime() {  
  return LinuxParser::UpTime();
}