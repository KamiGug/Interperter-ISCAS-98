#ifndef FLIPFLOP_H
#define FLIPFLOP_H
#define DEFAULT_ENTER_STATE_FLIPFLOP LOW_LEVEL

#include "../Gate.h"

class FlipFlop : public Gate
{
public:
	FlipFlop(std::vector<Signal*> inputs, Signal* output, std::string label = "", Signal* clock = nullptr);
	~FlipFlop();
	virtual bool isReady();
	virtual value_t calculateValue();
	virtual value_t calculateValueToSave() = 0;
	virtual bool isBad() = 0;
	virtual void reset();
	virtual void save();

protected:
	Signal* clock;
	value_t savedValue;
	value_t prevClockValue;

private:

};


#endif