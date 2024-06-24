#ifndef XNORGATE_H
#define XNORGATE_H

#include "Gate.h"

class XnorGate : public Gate {
public:
	XnorGate(std::vector<Signal*> inputs, Signal* output, std::string label = "")
		:Gate(inputs, output, label) {	}


protected:
	virtual value_t calculateValue(fault_t withThisFault = NO_FAULT);

	virtual bool isBad();

private:

};
#endif