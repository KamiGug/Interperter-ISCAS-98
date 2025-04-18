
#ifndef SIGNAL_H
#define SIGNAL_H
#include <string>
#include <stdexcept>
#include <vector>

#include "Value.h"




class Signal {
public:

	static std::vector<Signal*> signals;
	static std::vector<Signal*> inputs;
	static std::vector<Signal*> outputs;

	static Signal* getSignal(std::string label, value_t valueToSetIfNonexistent = UNKNOWN_VALUE);

	static void addSignal(std::string label, value_t value = UNKNOWN_VALUE, bool isOutput = false, bool isInput = false);

	static void setSignalAsInputOrOutput(std::string label, bool isOutput = false, value_t value = UNKNOWN_VALUE);

	static std::vector<Signal*> buildFromLabels(std::vector<std::string> labels);

	static void unsetAllSignals();

	static bool allSignalsSet();

	static int countInput();

	static int countOutput();

	static void setInputs(std::vector<value_t> values);

	static std::vector<Signal*> getInputs();

	static std::vector<Signal*> getOutputs();

	std::string getLabel();

	value_t getValue();

	void setValue(value_t value);

	void setOutput();

	void unsetOutput();

	Signal(std::string label, value_t value = UNKNOWN_VALUE, bool isOutput = false);

	Signal(Signal* signalToCopy);

	static void tickClock();

	static void setClock(value_t value = UNKNOWN_VALUE);

	static Signal* getClock();

private:

	bool isOutput;
	std::string label;
	value_t value;
	static std::vector<Signal*> constSignals;
	static Signal* clock;
};
#endif // !SIGNAL_H