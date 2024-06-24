#ifndef XORGATE_H
#define XORGATE_H

#include "Gate.h"

class XorGate : public Gate {
public:
	XorGate(std::vector<Signal*> inputs, Signal* output, std::string label = "")
		:Gate(inputs, output, label) {	}


protected:
	virtual value_t calculateValue(fault_t withThisFault = NO_FAULT);

	virtual bool isBad();

private:

};
#endif