#ifndef RESULTS_H
#define RESULTS_H


#include "Fault/Fault.h"
#include "Signal.h"
#include "subresults.h"

typedef struct RESULTS {
	Fault* fault;
	std::vector<Signal*> inputs;
	std::vector<Subresults_t*> clockIntervals;

	RESULTS(Fault* fault, std::vector<Signal*> inputs) {
		this->fault = (fault!=nullptr ? fault->copy() : nullptr);
		//std::vector<Signal*>::iterator i;
		for (std::vector<Signal*>::iterator i = inputs.begin(); i != inputs.end(); i++) {
			this->inputs.push_back(new Signal(*i));
		}
		//for (i = outputs.begin(); i != outputs.end(); i++) {
		//	this->outputs.push_back(new Signal(*i));
		//}
	}

	~RESULTS() {
		if (this->fault) {
			delete this->fault;
			this->fault = nullptr;
		}
	}

	void appendOutput(std::vector<Signal*> outputs, value_t clockState) {
		clockIntervals.push_back(new Subresults_t (outputs, clockState));
	}

	void appendOutput(std::vector<Signal*> outputs, Signal* clock) {
		clockIntervals.push_back(new Subresults_t(outputs, clock));
	}

} Results_t;



#endif