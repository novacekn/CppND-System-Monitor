#ifndef PROCESS_H
#define PROCESS_H

#include <string>

#include "linux_parser.h"
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int pid, std::string user, std::string command, long active_jiffies, std::string ram, long int uptime) {
	this->pid_ = pid;
	this->user_ = user;
	this->command_ = command;
	this->cpu_utilization_ = (float)active_jiffies / (float)LinuxParser::Jiffies();
	this->ram_ = ram;
	this->uptime_ = uptime;
  }
  int Pid();                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp

  // TODO: Declare any necessary private members
 private:
  int pid_;
  std::string user_, command_, ram_;
  long uptime_;
  float cpu_utilization_;
};

#endif
