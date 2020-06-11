#include "ncurses_display.h"
#include "system.h"
#include <iostream>
#include "linux_parser.h"
#include <thread>
#include <chrono>


int main() {
  System system;
  NCursesDisplay::Display(system);
  
//   std::cout << "Total Jiffies" << LinuxParser::Jiffies() << std::endl;
//   while(1){
//     auto processes = system.Processes();
//     for (auto process:processes){
//       std::cout << "Pid -> " << process.Pid() << " ActiveJiffies -> " << LinuxParser::ActiveJiffies(process.Pid()) << "  Total Jiffies" << LinuxParser::Jiffies() << std::endl;;
//       std::cout << "Pid -> " << process.Pid() << " cpu  -> " << process.CpuUtilization() << std::endl ;
//     }
//     std::this_thread::sleep_for(std::chrono::seconds(25));
//   }
}