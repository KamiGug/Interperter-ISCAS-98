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

	static void appendGate(Gate* gate);

	static void setOutputOfAllGates();

	static Gate* getGateByLabel(std::string label);

	static int countFlipFlops();

	std::string getLabel();

	void setOutputValue();

	Signal* getOutput();

	virtual bool isReady();

	value_t getOutputValue();

	std::vector<Signal*> getInputs();

	void addInput(std::string inputLabel);

	void addInput(Signal* input);

	void removeInput(std::string inputLabel);

	void removeInput(Signal* input);

	virtual void reset();

	static void resetAll();

	Gate(std::vector<Signal*> inputs, Signal* output, std::string label = "");

protected:
	static std::vector<Gate*> gates;
	std::string error = "Gate is incorrectly created!";
	std::vector<Signal*> inputs;
	Signal* output;

	virtual value_t calculateValue() = 0;

	virtual bool isBad();

private:
	std::string label;
	void setInput(std::vector<Signal*> inputs);
	void setOutput(Signal* output);

};

#endif