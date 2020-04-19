#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;



// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() {
	for (int pid : LinuxParser::Pids()) {
		Process p = Process(
				pid,
				LinuxParser::User(pid),
				LinuxParser::Command(pid),
				LinuxParser::ActiveJiffies(pid),
				LinuxParser::Ram(pid),
				LinuxParser::UpTime(pid)
				);
		processes_.push_back(p);
	}
	return processes_; 
}



// COMPLETED IMPLEMENTATIONS
Processor& System::Cpu() { return cpu_; }

float System::MemoryUtilization() { return memory_utilization_; }

std::string System::Kernel() { return kernel_; }

std::string System::OperatingSystem() { return operating_system_; }

int System::RunningProcesses() { return running_processes_; }

int System::TotalProcesses() { return total_processes_; }

long System::UpTime() { return uptime_; }
