#ifndef ANDGATE_C
#define ANDGATE_C

#include "AndGate.h"

value_t AndGate::calculateValue(fault_t withThisFault) {
	if (withThisFault == STUCK_AT_0) return LOW_LEVEL;
	if (withThisFault == STUCK_AT_1) return HIGH_LEVEL;
	if (!(this->isReady())) return UNKNOWN_VALUE;
	std::vector<Signal*>::iterator i = inputs.begin();
	while (i != inputs.end()) {
		if ((*i)->getValue() == LOW_LEVEL) return LOW_LEVEL;
		i++;
	}
	return HIGH_LEVEL;
}

bool AndGate::isBad() {
	return inputs.size() < 2;
}
#endif