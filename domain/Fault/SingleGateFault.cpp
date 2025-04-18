#ifndef SINGLEFAULT_C
#define SINGLEFAULT_C

#include "SingleGateFault.h"

SingleGateFault::SingleGateFault(std::string gateLabel, value_t type) {
	this->gate = Gate::getGateByLabel(gateLabel);
	this->type = type;
	this->description = gateLabel;
}

SingleGateFault::SingleGateFault(SingleGateFault* faultToCopy) {
	this->gate = faultToCopy->gate;
	this->type = faultToCopy->type;
	this->description = faultToCopy->description;
}

void SingleGateFault::apply() {
	if (this->type == UNKNOWN_VALUE) return;
	this->gate->getOutput()->setValue(this->type);
}

void SingleGateFault::revert() {
	if (this->type == UNKNOWN_VALUE) return;
	this->gate->getOutput()->setValue(UNKNOWN_VALUE);
}

SingleGateFault* SingleGateFault::copy() {
	return new SingleGateFault(this);
}




#endif