#include "gateFactory.h"

//std::map<std::string, std::function<Gate* (std::vector<std::string> inputs, std::string output)>> gateFactory

gateFactory_t* initGateFactory() {
	gateFactory_t* tmp = new gateFactory_t();
	(*tmp)["and"] = 
	[&](std::vector<std::string> inputs, std::string output, std::string clk) -> AndGate* {
			return new AndGate(Signal::buildFromLabels(inputs), Signal::getSignal(output), output);
	};

	(*tmp)["or"] = 
	[&](std::vector<std::string> inputs, std::string output, std::string clk) -> OrGate* {
		return new OrGate(Signal::buildFromLabels(inputs), Signal::getSignal(output), output);
	};

	(*tmp)["nand"] =
		[&](std::vector<std::string> inputs, std::string output, std::string clk) -> NandGate* {
		return new NandGate(Signal::buildFromLabels(inputs), Signal::getSignal(output), output);
	};

	(*tmp)["nor"] =
		[&](std::vector<std::string> inputs, std::string output, std::string clk) -> NorGate* {
		return new NorGate(Signal::buildFromLabels(inputs), Signal::getSignal(output), output);
	};

	(*tmp)["not"] =
		[&](std::vector<std::string> inputs, std::string output, std::string clk) -> NotGate* {
		return new NotGate(Signal::buildFromLabels(inputs), Signal::getSignal(output), output);
	};

	(*tmp)["xnor"] =
		[&](std::vector<std::string> inputs, std::string output, std::string clk) -> XnorGate* {
		return new XnorGate(Signal::buildFromLabels(inputs), Signal::getSignal(output), output);
	};

	(*tmp)["xor"] =
		[&](std::vector<std::string> inputs, std::string output, std::string clk) -> XorGate* {
		return new XorGate(Signal::buildFromLabels(inputs), Signal::getSignal(output), output);
	};

	(*tmp)["dff"] =
		[&](std::vector<std::string> inputs, std::string output, std::string clk = "") -> DFlipFlop* {
		if (clk == "") {
			return new DFlipFlop(Signal::buildFromLabels(inputs), Signal::getSignal(output), output);
		}
		else {
			return new DFlipFlop(Signal::buildFromLabels(inputs), Signal::getSignal(output), output, Signal::getSignal(clk));
		}
	};

	return tmp;
}

void killGateFactory(gateFactory_t* toKill) {
	(*toKill).clear();
	delete toKill;
}