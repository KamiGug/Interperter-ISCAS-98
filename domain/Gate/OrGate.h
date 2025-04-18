#ifndef ORGATE_H
#define ORGATE_H

#include "Gate.h"

class OrGate : public Gate {
public:
	OrGate(std::vector<Signal*> inputs, Signal* output, std::string label = "")
		:Gate(inputs, output, label) {	}


protected:
	virtual value_t calculateValue();

	virtual bool isBad();

private:

};
#endif
