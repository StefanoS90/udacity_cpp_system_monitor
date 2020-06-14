#include "processor.h"
#include "linux_parser.h"



// TODO: Return the aggregate CPU utilization
float Processor::Utilization(){

  auto utilization_info = LinuxParser::CpuUtilization();
  
  float user = std::stof(utilization_info[0]);
  float nice = std::stof(utilization_info[1]);
  float system = std::stof(utilization_info[2]);
  float idle = std::stof(utilization_info[3]);
  float iowait = std::stof(utilization_info[4]);
  float irq = std::stof(utilization_info[5]);
  float softirq = std::stof(utilization_info[6]);
  float steal = std::stof(utilization_info[7]);
  //float guest = std::stof(utilization_info[8]);
  //float guest_nice = std::stof(utilization_info[9]);
  
  float cpu_non_idle = user + nice + system + irq + softirq + steal;
  float cpu_idle  = idle + iowait;
  float cpu_total = cpu_idle + cpu_non_idle;
  
  float totald = cpu_total - this->prev_cpu_total;
  float idled = cpu_idle - this->prev_cpu_idle;
  
  this->prev_cpu_idle  = cpu_idle;
  this->prev_cpu_total = cpu_total;
  
  return  (totald - idled)/totald;

  
}

