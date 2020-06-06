#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp
  Processor():prev_cpu_idle(0), prev_cpu_total(0) {};

  // TODO: Declare any necessary private members
 private:
   float prev_cpu_idle;
   float prev_cpu_total;
};

#endif


  
  
  
