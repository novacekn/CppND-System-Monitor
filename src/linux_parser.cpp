#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::stoi;
using std::stol;
using std::string;
using std::to_string;
using std::vector;

string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    if (file->d_type == DT_DIR) {
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

int LinuxParser::TotalProcesses() {
	string line, key, value;
	std::ifstream filestream(kProcDirectory + kStatFilename);
	if (filestream.is_open()) {
		while (std::getline(filestream, line)) {
			std::istringstream linestream(line);
			while (linestream >> key >> value) {
				if (key == "processes") {
					return stoi(value);
				}
			}
		}
	}
	return 0; 
}

int LinuxParser::RunningProcesses() {
	string line, key, value;
	std::ifstream filestream(kProcDirectory + kStatFilename);
	if (filestream.is_open()) {
		while (std::getline(filestream, line)) {
			std::istringstream linestream(line);
			while (linestream >> key >> value) {
				if (key	== "procs_running") {
					return stoi(value);
				}
			}
		}
	}
	return 0; 
}

long LinuxParser::UpTime() {
	string line, system, idle;
	std::ifstream filestream(kProcDirectory + kUptimeFilename);
	if (filestream.is_open()) {
		std::getline(filestream, line);
		std::istringstream linestream(line);
		linestream >> system >> idle;
		return stol(system) + stol(idle);  // Not positive if I was supposed to add the two number to get total time or not
	}
	return 0;
}

float LinuxParser::MemoryUtilization() {
	string line, key, value, kb;
	float mem_total, mem_free;
	std::ifstream filestream(kProcDirectory + kMeminfoFilename);
	if (filestream.is_open()) {
		while (std::getline(filestream, line)) {
			std::istringstream linestream(line);
			while (linestream >> key >> value >> kb) {
				if (key == "MemTotal:") {
					mem_total = stof(value);
				} else if (key == "MemFree:") {
					mem_free = stof(value);
				}
			}
		}
	}
	return ((mem_total - mem_free) / mem_total);
}

long LinuxParser::ActiveJiffies() {
	string line, cpu, user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
	std::ifstream filestream(kProcDirectory + kStatFilename);
	if (filestream.is_open()) {
		std::getline(filestream, line);
		std::istringstream linestream(line);
		while (linestream >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice) {
			if (cpu == "cpu") {
				return stol(user) + stol(nice) + stol(system) + stol(irq) + stol(softirq) + stol(steal) + stol(guest) + stol(guest_nice);
			}
		}
	}
	return 0; 
}

long LinuxParser::IdleJiffies() {
	string line, cpu, user, nice, system, idle, iowait;
	std::ifstream filestream(kProcDirectory + kStatFilename);
	if (filestream.is_open()) {
		while (std::getline(filestream, line)) {
			std::istringstream linestream(line);
			while (linestream >> cpu >> user >> nice >> system >> idle >> iowait) {
				if (cpu == "cpu") {
					return stol(idle) + stol(iowait);
				}
			}
		}
	}
	return 0; 
}

long LinuxParser::Jiffies() { return ActiveJiffies() + IdleJiffies(); }

long LinuxParser::ActiveJiffies(int pid) {
	string line, pid_, comm, state, ppid, pgrp, session, tty_nr, tpgid, flags, minflt, cminflt, majflt, cmajflt, utime, stime,
	       cutime, cstime, priority, nice, num_threads, itrealvalue, starttime;
	std::ifstream filestream(kProcDirectory + to_string(pid) + kStatFilename);
	if (filestream.is_open()) {
		std::getline(filestream, line);
		std::istringstream linestream(line);
		linestream >> pid_ >> comm >> state >> ppid >> pgrp >> session >> tty_nr >> tpgid >> flags >> minflt >> cminflt
			   >> majflt >> cmajflt >> utime >> stime >> cutime >> cstime >> priority >> nice >> num_threads >> itrealvalue >> starttime;
		return stol(utime) + stol(stime) + stol(cutime) + stol(cstime) + stol(starttime);
	}
	return 0; 
}

string LinuxParser::Command(int pid) {
	string line, cmd;
	std::ifstream filestream(kProcDirectory + to_string(pid) + kCmdlineFilename);
	if (filestream.is_open()) {
		std::getline(filestream, line);
		std::istringstream linestream(line);
		linestream >> cmd;
	}
	return cmd;
}

string LinuxParser::Ram(int pid) {
	string line, key, value;
	std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
	if (filestream.is_open()) {
		while (std::getline(filestream, line)) {
			std::istringstream linestream(line);
			while (linestream >> key >> value) {
				if (key == "VmSize:") {
					std::replace(value.begin(), value.end(), 'k', ' ');
					std::replace(value.begin(), value.end(), 'B', ' ');
					return to_string((int)(stol(value) * 0.001));
				}
			}
		}
	}
	return string(); 
}

string LinuxParser::Uid(int pid) {
	string line, key, value;
	std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
	if (filestream.is_open()) {
		while (std::getline(filestream, line)) {
			std::istringstream linestream(line);
			while (linestream >> key >> value) {
				if (key == "Uid:") {
					return value;
				}
			}
		}
	}
	return string(); 
}

string LinuxParser::User(int pid) {
	string uid = LinuxParser::Uid(pid);
	string line, user, passwd, uid_, gid, gecos, dir, shell;
	std::ifstream filestream(kPasswordPath);
	if (filestream.is_open()) {
		while (std::getline(filestream, line)) {
			std::replace(line.begin(), line.end(), ':', ' ');
			std::istringstream linestream(line);
			while (linestream >> user >> passwd >> uid_ >> gid >> gecos >> dir >> shell) {
				if (uid_ == uid) {
					return user;
				}
			}
		}
	}
	return string(); 
}

long LinuxParser::UpTime(int pid) {
	string line, pid_, comm, state, ppid, pgrp, session, tty_nr, tpgid, flags, minflt, cminflt, majflt, cmajflt,
	       utime, stime, cutime, cstime, priority, nice, num_threads, itrealvalue, starttime;
	long st;
	std::ifstream filestream(kProcDirectory + to_string(pid) + kStatFilename);
	if (filestream.is_open()) {
		std::getline(filestream, line);
		std::istringstream linestream(line);
		linestream >> pid_ >> comm >> state >> ppid >> pgrp >> session >> tty_nr >> tpgid >> minflt >> cminflt
			   >> majflt >> cmajflt >> utime >> stime >> cutime >> cstime >> priority >> nice >> num_threads
			   >> itrealvalue >> starttime;
		st = stol(starttime);
	}
	return st / sysconf(_SC_CLK_TCK);
}
