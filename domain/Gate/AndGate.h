#ifndef ANDGATE_H
#define ANDGATE_H

#include "Gate.h"

class AndGate : public Gate {
public:
	AndGate(std::vector<Signal*> inputs, Signal* output, std::string label = "")
		:Gate(inputs, output, label) {	}


protected:
	virtual value_t calculateValue();

	virtual bool isBad();

private:

};

#endif