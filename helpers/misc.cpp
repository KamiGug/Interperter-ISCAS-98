#include "misc.h"


std::string getValueName(value_t val) {
	switch (val)
	{
	case UNKNOWN_VALUE:
		return "UNKNOWN VALUE";

	case LOW_LEVEL:
		return "LOW LEVEL";

	case HIGH_LEVEL:
		return "HIGH LEVEL";

	default:
		return "Not A Value";
	}
}

int power(int base, int exponent) {
	int tmp = 1;
	for (; exponent > 0; exponent--) {
		tmp *= base;
	}
	return tmp;
}

// trim from start (in place)
void ltrim(std::string& s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
		return !std::isspace(ch);
		}));
}

// trim from end (in place)
void rtrim(std::string& s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
		return !std::isspace(ch);
		}).base(), s.end());
}

// trim from both ends (in place)
void trim(std::string& s) {
	rtrim(s);
	ltrim(s);
}