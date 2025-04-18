#ifndef NOTGATE_C
#define NOTGATE_C

#include "NotGate.h"

value_t NotGate::calculateValue() {
	if (!(this->isReady()))	return UNKNOWN_VALUE;
	if (inputs.at(0)->getValue() == HIGH_LEVEL) return LOW_LEVEL;
	else return HIGH_LEVEL;
}

bool NotGate::isBad() {
	return inputs.size() != 1;
}

#endif