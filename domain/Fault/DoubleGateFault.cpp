//change input signal of the second gate that is an output of the first gate
#ifndef DOUBLEFAULT_C
#define DOUBLEFAULT_C

#include "DoubleGateFault.h"

DoubleGateFault::DoubleGateFault(std::string gateLabelFrom, std::string gateLabelTo, value_t type) {
	this->gateFrom = Gate::getGateByLabel(gateLabelFrom);
	this->gateTo = Gate::getGateByLabel(gateLabelTo);
	//this->prev = gateFrom->getOutput();
	this->type = type;
	this->description = gateFrom->getLabel() + " -> " + gateTo->getLabel();
	this->faultySignal = new Signal("FAULT-" + gateLabelFrom, type, true);
	
}

DoubleGateFault::DoubleGateFault(DoubleGateFault* faultToCopy) {
	this->gateFrom = faultToCopy->gateFrom;
	this->gateTo = faultToCopy->gateTo;
	//this->prev = faultToCopy->prev;
	this->faultySignal = new Signal(faultToCopy->faultySignal);
	this->description = faultToCopy->description;
	this->type = faultToCopy->type;
}

void DoubleGateFault::apply() {
	this->gateTo->removeInput(this->gateFrom->getOutput());
	this->gateTo->addInput(faultySignal);
}

void DoubleGateFault::revert() {
	this->gateTo->removeInput(faultySignal);
	this->gateTo->addInput(this->gateFrom->getOutput());
}

DoubleGateFault* DoubleGateFault::copy() {
	return new DoubleGateFault(this);
}




#endif