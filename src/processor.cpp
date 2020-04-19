#include "processor.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
	float cpu_utilization = (total_jiffies_ - idle_jiffies_) / total_jiffies_;
	return cpu_utilization * 100;
}
