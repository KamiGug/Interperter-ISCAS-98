#ifndef GATE_C
#define GATE_C


#include "Gate.h"

void Gate::setInput(std::vector<Signal*> inputs) {
	this->inputs.swap(inputs);
}

void Gate::setOutput(Signal* output) {
	this->output = output;
	output->setOutput();
}

void Gate::setOutputValue() {
	output->setValue(this->calculateValue());
}

bool Gate::isReady() {
	std::vector<Signal*>::iterator i = inputs.begin();
	while (i != inputs.end()) {
		if ((*i)->getValue() == UNKNOWN_VALUE) return false;
		i++;
	}
	return true;
}

value_t Gate::getOutputValue() {
	return output->getValue();
}

Gate::Gate(std::vector<Signal*> inputs, Signal* output, std::string label) {
	setInput(inputs);
	setOutput(output);
	this->label = label;
	if (isBad()) throw std::runtime_error(this->error);
}

bool Gate::isBad() {
	return false;
}

std::vector<Gate*> Gate::gates;

void Gate::appendGate(Gate* gate) {
	gates.push_back(gate);
}

void Gate::setOutputOfAllGates() {
	std::vector<Gate*>::iterator i;
	bool somethingChanged;
	while (!Signal::allSignalsSet()) {
		somethingChanged = false;
		i = gates.begin();
		while (i != gates.end()) {
			if ((*i)->isReady() && (*i)->getOutputValue() == UNKNOWN_VALUE) //is ready and output is unset
			{
				(*i)->setOutputValue();
				somethingChanged = true;
			}
			i++;
		}
		if (!somethingChanged) {
			throw std::runtime_error("Unable to process all gates! There maybe some orphaned gates.");
		}
	}
}

#endif