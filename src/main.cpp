#include "ncurses_display.h"
#include "system.h"
#include <iostream>

int main() {
  System system;
  NCursesDisplay::Display(system);
//   std::cout << system.Cpu().Utilization() << std::endl ;
    
}