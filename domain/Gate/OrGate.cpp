#ifndef ORGATE_C
#define ORGATE_C

#include "OrGate.h"

value_t OrGate::calculateValue(fault_t withThisFault) {
	if (withThisFault == STUCK_AT_0) return LOW_LEVEL;
	if (withThisFault == STUCK_AT_1) return HIGH_LEVEL;
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