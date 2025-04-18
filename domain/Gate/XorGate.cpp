#ifndef XORGATE_C
#define XORGATE_C

#include "XorGate.h"

value_t XorGate::calculateValue() {
	if (!isReady())	return UNKNOWN_VALUE;
	bool isEven = true;
	std::vector<Signal*>::iterator i = inputs.begin();
	while (i != inputs.end()) {
		if ((*i)->getValue() == HIGH_LEVEL) isEven = !isEven;
		i++;
	}
	return isEven ? LOW_LEVEL : HIGH_LEVEL;
}

bool XorGate::isBad() {
	return inputs.size() < 2;
}
#endif