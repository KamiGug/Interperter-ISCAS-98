#ifndef NORGATE_C
#define NORGATE_C

#include "NorGate.h"

value_t NorGate::calculateValue() {
	if (!(this->isReady()))	return UNKNOWN_VALUE;
	std::vector<Signal*>::iterator i = inputs.begin();
	while (i != inputs.end()) {
		if ((*i)->getValue() == HIGH_LEVEL) return LOW_LEVEL;
		i++;
	}
	return HIGH_LEVEL;
}

bool NorGate::isBad() {
	return inputs.size() < 2;
}
#endif