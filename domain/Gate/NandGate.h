#ifndef NANDGATE_H
#define NANDGATE_H

#include "Gate.h"

class NandGate : public Gate {
public:
	NandGate(std::vector<Signal*> inputs, Signal* output, std::string label = "")
		:Gate(inputs, output, label) {	}


protected:
	virtual value_t calculateValue();

	virtual bool isBad();

private:

};
#endif
