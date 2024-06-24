#ifndef GATE_H
#define GATE_H

#include <vector>
#include <stdexcept>

#include "..\Value.h"
#include "..\Signal.h"

#ifndef FAULT_ENUM
#define FAULT_ENUM
typedef enum {NO_FAULT = 0, STUCK_AT_0 = 10, STUCK_AT_1 = 20} fault_t;

#endif // !FAULT_ENUM




class Gate {
public:
	static std::vector<Gate*> gates;

	static void appendGate(Gate* gate);

	static void setOutputOfAllGates();

	void setOutputValue();

	bool isReady();

	value_t getOutputValue();

	Gate(std::vector<Signal*> inputs, Signal* output, std::string label = "");

protected:
	std::string error = "Gate is incorrectly created!";
	std::vector<Signal*> inputs;
	Signal* output;

	virtual value_t calculateValue(fault_t withThisFault = NO_FAULT) = 0;

	virtual bool isBad();

private:
	std::string label;
	void setInput(std::vector<Signal*> inputs);
	void setOutput(Signal* output);

};

#endif