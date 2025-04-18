#ifndef ORGATE_C
#define ORGATE_C

#include "OrGate.h"

value_t OrGate::calculateValue() {
	if (!(this->isReady()))	return UNKNOWN_VALUE;
	std::vector<Signal*>::iterator i = inputs.begin();
	while (i != inputs.end()) {
		if ((*i)->getValue() == HIGH_LEVEL) return HIGH_LEVEL;
		i++;
	}
	return LOW_LEVEL;
}

bool OrGate::isBad() {
	return inputs.size() < 2;
}
#endif