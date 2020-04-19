#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "linux_parser.h"

class Processor {
 public:
  float Utilization();

 private:
  long total_jiffies_ = LinuxParser::Jiffies();
  long active_jiffies_ = LinuxParser::ActiveJiffies();
  long idle_jiffies_ = LinuxParser::IdleJiffies();
};

#endif
