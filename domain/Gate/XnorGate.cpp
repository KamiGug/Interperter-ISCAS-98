#ifndef XNORGATE_C
#define XNORGATE_C

#include "XnorGate.h"

value_t XnorGate::calculateValue() {
	if (!(this->isReady()))	return UNKNOWN_VALUE;
	bool isEven = true;
	std::vector<Signal*>::iterator i = inputs.begin();
	while (i != inputs.end()) {
		if ((*i)->getValue() == HIGH_LEVEL) isEven = !isEven;
		i++;
	}
	return isEven ? HIGH_LEVEL : LOW_LEVEL;
}

bool XnorGate::isBad() {
	return inputs.size() < 2;
}
#endif