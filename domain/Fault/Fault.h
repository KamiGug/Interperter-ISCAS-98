#ifndef FAULT_H
#define FAULT_H

#include <string>

#include "../Value.h"
#include "../Gate/Gate.h"



class Fault {
public:
	Fault();
	Fault(value_t type);
	Fault(Fault* faultToCopy);

	~Fault();

	virtual Fault* copy() = 0;
	virtual void apply() = 0;
	virtual void revert() = 0;
	value_t getType();
	//std::string getGateLabel();
	std::string getDescription();

protected:
	value_t type;
	std::string description;


private:
	
};



#endif