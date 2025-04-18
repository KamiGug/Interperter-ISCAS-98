#ifndef NANDGATE_C
#define NANDGATE_C

#include "NandGate.h"

value_t NandGate::calculateValue() {
	if (!(this->isReady()))	return UNKNOWN_VALUE;
	std::vector<Signal*>::iterator i = inputs.begin();
	while (i != inputs.end()) {
		if ((*i)->getValue() == LOW_LEVEL) return HIGH_LEVEL;
		i++;
	}
	return LOW_LEVEL;
}

bool NandGate::isBad() {
	return inputs.size() < 2;
}
#endif