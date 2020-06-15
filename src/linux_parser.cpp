#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>
#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  string line;
  string key;
  string value;
  string unit;
  float mem_available;
  float mem_tot;
  float mem_utilization;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value >> unit) {
        if (key == "MemAvailable") {
          mem_available = std::stof( value);
        }
        if (key == "MemTotal"){
	  mem_tot = std::stof( value);
	}
      }
    }
  }
  mem_utilization = ((mem_tot - mem_available)/mem_tot);
  return mem_utilization;
}


// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  string uptime;
  string line;
  string word;
  std::ifstream filestream(kProcDirectory + kUptimeFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> uptime;
      }
    }
  return std::stoi(uptime);
 }
// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() {
  float uptime = LinuxParser::UpTime();
  float sys_freq = sysconf(_SC_CLK_TCK); 
  return uptime*sys_freq;
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies() { 
  
  auto cpu_stats = LinuxParser::CpuUtilization();
  long active_jiffies = 0;
  for (auto stat: cpu_stats){
    active_jiffies += std::stoi(stat);
  }
  return active_jiffies;
}

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies(int pid) { 
  string line;
  string word;
  float utime; 
  float stime;
  float cutime;
  float cstime;
  
  vector<string> proc_stat;
  std::ifstream filestream(kProcDirectory + "/" + std::to_string(pid) + kStatFilename);
  if (filestream.is_open()) {
      std::getline(filestream, line);
      std::istringstream linestream(line);
      while (linestream >> word){
	proc_stat.push_back(word);
      }
  }
  
  utime = std::stoi(proc_stat[13]);
  stime = std::stoi(proc_stat[14]);
  cutime = std::stoi(proc_stat[15]);
  cstime = std::stoi(proc_stat[16]);
  return (utime+stime+cutime+cstime);
}

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  string line;
  string word;
  vector<std::string> out_string;
  
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
      std::getline(filestream, line);
      std::istringstream linestream(line);
      linestream >> word;
      while (linestream >> word){
	out_string.push_back(word);
      }
    }
  return out_string;
 }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() 
{ 
  string line;
  string word;
  string num_processes;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> word) {
        if (word == "processes") linestream >> num_processes;
        }
      }
    }
    return std::stoi(num_processes);
 }



// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() 
{ 
  string line;
  string word;
  string runn_processes;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> word) {
        if (word == "procs_running") linestream >> runn_processes;
        }
      }
    }
    return std::stoi(runn_processes);
 }

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid)  { 
  string line;
  std::ifstream filestream(kProcDirectory + "/" + std::to_string(pid) + kCmdlineFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
    }
  } 
  return line; }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  string line;
  string key;
  string value;
  string process_ram = "0";
  std::ifstream filestream(kProcDirectory + "/" + std::to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value ) {
	// using vmData instead of VVmSize becuase i want to account for physical memory 
        if (key == "VmData") {
          process_ram = value;
	  process_ram = process_ram.substr(0, process_ram.size()-4);
        }
      }
    }
  } 
  return process_ram; }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  string line;
  string key;
  string value;
  string process_uid;
  std::ifstream filestream(kProcDirectory + "/" + std::to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value ) {
        if (key == "Uid") {
          process_uid = value;
        }
      }
    }
  } 
  return process_uid; }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) 
{ 
  string process_uid = LinuxParser::Uid(pid);
  string process_username;
  string line;
  string username;
  string word;
  string uid;
  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> username >> word >> uid ) {
        if (uid == process_uid) {
          process_username = username;
        }
      }
    }
  } 
  
 return process_username;  
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
  { 
  vector<string> proc_stat;
  string word;
  string line;
  std::ifstream filestream(kProcDirectory + "/" + std::to_string(pid) + kStatFilename);
  if (filestream.is_open()) {
      std::getline(filestream, line);
      std::istringstream linestream(line);
      while (linestream >> word){
	proc_stat.push_back(word);
      }
  }
  
  int start_time = std::stoi(proc_stat[21]);
  float sys_freq = sysconf(_SC_CLK_TCK);
  return UpTime() - start_time/sys_freq;
}
  
  
}