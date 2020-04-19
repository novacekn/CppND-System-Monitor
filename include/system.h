#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "linux_parser.h"

class System {
 public:
  Processor& Cpu();                   // TODO: See src/system.cpp
  std::vector<Process>& Processes();  // TODO: See src/system.cpp
  float MemoryUtilization();
  long UpTime();
  int TotalProcesses();
  int RunningProcesses();
  std::string Kernel();
  std::string OperatingSystem();

 private:
  std::string kernel_ = LinuxParser::Kernel();
  std::string operating_system_ = LinuxParser::OperatingSystem();
  int total_processes_ = LinuxParser::TotalProcesses();
  int running_processes_ = LinuxParser::RunningProcesses();
  long uptime_ = LinuxParser::UpTime();
  float memory_utilization_ = LinuxParser::MemoryUtilization();
  Processor cpu_ = Processor();
  std::vector<Process> processes_ = {};
};

#endif
