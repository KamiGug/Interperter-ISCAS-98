#ifndef FAULT_C
#define FAULT_C

#include "Fault.h"

Fault::Fault() {
	this->type = UNKNOWN_VALUE;
}

Fault::Fault(value_t type) {
	this->type = type;
}

Fault::Fault(Fault* faultToCopy) {
	//this->gateLabel = faultToCopy->gateLabel;
	this->type = faultToCopy->type;
}

Fault::~Fault() {

}

//void Fault::apply() {
//	Gate::getGateByLabel(gateLabel)->getOutput()->setValue(this->type);
//}

value_t Fault::getType()
{
	return type;
}

std::string Fault::getDescription()
{
	return this->description;
}

//std::string Fault::getGateLabel()
//{
//	return gateLabel;
//}



#endif


