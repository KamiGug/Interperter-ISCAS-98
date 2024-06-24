#ifndef NOTGATE_H
#define NOTGATE_H

#include "Gate.h"

class NotGate : public Gate {
public:
	NotGate(std::vector<Signal*> inputs, Signal* output, std::string label = "")
		:Gate(inputs, output, label) {	}


protected:
	virtual value_t calculateValue(fault_t withThisFault = NO_FAULT);

	virtual bool isBad();

private:

};
#endif