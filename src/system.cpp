#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;



// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { return processes_; }

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { return 0; }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { return 0.0; }



// COMPLETED IMPLEMENTATIONS

std::string System::Kernel() { return System::Kernel(); }

std::string System::OperatingSystem() { return operating_system_; }

int System::RunningProcesses() { return running_processes_; }

int System::TotalProcesses() { return total_processes_; }
