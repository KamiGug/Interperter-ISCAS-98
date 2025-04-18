#ifndef NORGATE_H
#define NORGATE_H

#include "Gate.h"

class NorGate : public Gate {
public:
	NorGate(std::vector<Signal*> inputs, Signal* output, std::string label = "")
		:Gate(inputs, output, label) {	}


protected:
	virtual value_t calculateValue();

	virtual bool isBad();

private:

};
#endif