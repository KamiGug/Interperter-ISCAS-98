#ifndef SUBRESULTS_H
#define SUBRESULTS_H


#include "Fault/Fault.h"
#include "Signal.h"

typedef struct SUBRESULTS {
	std::vector<Signal*> outputs;
	value_t clock;

	SUBRESULTS(std::vector<Signal*> outputs, Signal * clock) {
		for (std::vector<Signal*>::iterator i = outputs.begin(); i != outputs.end(); i++) {
			this->outputs.push_back(new Signal(*i));
		}
		this->clock = clock->getValue();
	}

	SUBRESULTS(std::vector<Signal*> outputs, value_t clock) {
		for (std::vector<Signal*>::iterator i = outputs.begin(); i != outputs.end(); i++) {
			this->outputs.push_back(new Signal(*i));
		}
		this->clock = clock;
	}

} Subresults_t;



#endif