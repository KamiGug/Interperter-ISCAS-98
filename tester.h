// tester.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <vector>

#include "domain/Signal.h"

#include "domain/Gate/Gate.h"
#include "domain/Gate/AndGate.h"
#include "domain/Gate/NandGate.h"
#include "domain/Gate/NorGate.h"
#include "domain/Gate/NotGate.h"
#include "domain/Gate/OrGate.h"
#include "domain/Gate/XorGate.h"
#include "domain/Gate/XnorGate.h"


//TODO: DELETE THIS!!
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



// TODO: Reference additional headers your program requires here.
