#ifndef DFLIPFLOP_C
#define DFLIPFLOP_C

#include "DFlipFlop.h"

DFlipFlop::DFlipFlop(std::vector<Signal*> inputs, Signal* output, std::string label, Signal* clock)
	: FlipFlop(inputs, output, label, clock) {
	
}

//value_t DFlipFlop::calculateValue() {
//	return this->savedValue;
//	if (clock->getValue() == UNKNOWN_VALUE) return UNKNOWN_VALUE;
//	if (clock->getValue() == LOW_LEVEL) return savedValue;
//	if (clock->getValue() == HIGH_LEVEL) {
//		if (inputs[0]->getValue() != UNKNOWN_VALUE) {
//			savedValue = inputs[0]->getValue();
//		}
//		return savedValue;
//	}
//}

value_t DFlipFlop::calculateValueToSave() {
	return value_t(inputs[0]->getValue());
}

bool DFlipFlop::isBad() {
	return inputs.size() != 1 && clock != nullptr;
}


#endif