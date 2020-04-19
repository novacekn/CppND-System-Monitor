#include "processor.h"

float Processor::Utilization() {
	float cpu_utilization = ((float)total_jiffies_ - (float)idle_jiffies_) / (float)total_jiffies_;
	return cpu_utilization;
}
