#ifndef PROCESS_H
#define PROCESS_H
#include <chrono>
#include <string>

/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int pid):_pid(pid), prev_active_jiffies(0), prev_total_jiffies(0), cpu_utilization(0)  {
    this->last_update_tick = std::chrono::high_resolution_clock::now();
  }
  int Pid();                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp

  // TODO: Declare any necessary private members
 private:
   std::chrono::time_point<std::chrono::high_resolution_clock> last_update_tick;
   int _pid;
   long prev_active_jiffies;
   long prev_total_jiffies;
   float cpu_utilization;
   
   
};

#endif