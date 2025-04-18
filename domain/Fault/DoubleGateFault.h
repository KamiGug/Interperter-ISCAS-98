#ifndef DOUBLEFAULT_H
#define DOUBLEFAULT_H

#include "Fault.h"



class DoubleGateFault : public Fault {
public:

	DoubleGateFault(std::string gateLabelFrom = "", std::string gateLabelTo = "", value_t type = UNKNOWN_VALUE);
	DoubleGateFault(DoubleGateFault* faultToCopy);

	virtual void apply();
	virtual void revert();
	virtual DoubleGateFault* copy();

protected:




private:
	Gate* gateFrom;
	Gate* gateTo;  

	//Signal* prev;
	Signal* faultySignal;

};



#endif