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

std::string getValueNumberAsString(value_t val) {
	switch (val)
	{
	case UNKNOWN_VALUE:
		return "~";

	case LOW_LEVEL:
		return "0";

	case HIGH_LEVEL:
		return "1";

	default:
		return "/";
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

value_t getValueString(std::string str) {
	//normalize the string
	trim(str);
	for (auto& c : str) c = tolower(c);

	if (
		str == "0"
		|| str == "low"
		|| str == "low level"
		|| str == "low-level"
		|| str == "lowlevel"
		) {
		return LOW_LEVEL;
	}
	else if (
		str == "1"
		|| str == "high"
		|| str == "high level"
		|| str == "high-level"
		|| str == "highlevel"
		) {
		return HIGH_LEVEL;
	}
	else {
		throw std::runtime_error(
			"Unknown level in CSV test vector! Got: " + str
		);
	}
}

int countCharacter(std::string toTest, char toFind) {
	int count = 0;
	for (auto& c : toTest) if (c == toFind) count++;
	return count;
}