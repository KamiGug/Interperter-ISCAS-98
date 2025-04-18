#ifndef DFLIPFLOP_H
#define DFLIPFLOP_H

#include "FlipFlop.h"

class DFlipFlop : public FlipFlop
{
public:
	DFlipFlop(std::vector<Signal*> inputs, Signal* output, std::string label = "", Signal* clock = nullptr);
	//virtual value_t calculateValue();
	virtual value_t calculateValueToSave();
	virtual bool isBad();

protected:

private:

};


#endif