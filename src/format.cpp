#include <string>

#include "format.h"

using std::string;
using std::to_string;

string Format::ElapsedTime(long seconds) {
	long hours = seconds / 3600;
	seconds = seconds % 3600;
	long minutes = seconds / 60;
	seconds = seconds % 60;
	return to_string(hours) + ":" + to_string(minutes) + ":" + to_string(seconds);
}
