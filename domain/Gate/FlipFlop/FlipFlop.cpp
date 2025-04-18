#ifndef FLIPFLOP_C
#define FLIPFLOP_C

#include "FlipFlop.h"

FlipFlop::FlipFlop(std::vector<Signal*> inputs, Signal* output, std::string label, Signal* clock) 
	: Gate(inputs, output, label) {
	if (clock == nullptr) {
		this->clock = Signal::getClock();
	}
	else {
		this->clock = clock;
	}
	this->savedValue = DEFAULT_ENTER_STATE_FLIPFLOP;
}

FlipFlop::~FlipFlop() {
	if (this->clock != Signal::getClock()) delete clock;
}

bool FlipFlop::isReady()
{
	if (clock->getValue() == UNKNOWN_VALUE) return false;
	return true;
	//if (clock->getValue() == LOW_LEVEL) return true;
	//std::vector<Signal*>::iterator i = inputs.begin();
	//while (i != inputs.end()) {
	//	if ((*i)->getValue() == UNKNOWN_VALUE) return false;
	//	i++;
	//}
	//return true;
}

value_t FlipFlop::calculateValue() {
	return this->savedValue;
}

void FlipFlop::reset() {
	Gate::reset();
	this->savedValue = DEFAULT_ENTER_STATE_FLIPFLOP;
}

void FlipFlop::save() {
	if (this->prevClockValue == HIGH_LEVEL && this->clock->getValue() == LOW_LEVEL) {
		this->savedValue = calculateValueToSave();
	}
	this->prevClockValue = this->clock->getValue();
}

#endif