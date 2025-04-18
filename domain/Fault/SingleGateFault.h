#ifndef SINGLEFAULT_H
#define SINGLEFAULT_H

#include "Fault.h"



class SingleGateFault : public Fault {
public:
	SingleGateFault(std::string gateLabel, value_t type);
	SingleGateFault(SingleGateFault* faultToCopy);
	
	virtual void apply();
	virtual void revert();
	virtual SingleGateFault* copy();
	//std::string getGateLabel();

protected:




private:
	Gate* gate;
};



#endif