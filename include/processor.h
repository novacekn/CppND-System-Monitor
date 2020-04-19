#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "linux_parser.h"

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

 private:
  long total_jiffies_ = LinuxParser::Jiffies();
  long active_jiffies_ = LinuxParser::ActiveJiffies();
  long idle_jiffies_ = LinuxParser::IdleJiffies();
};

#endif
