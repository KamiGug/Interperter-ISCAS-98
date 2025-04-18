#ifndef GATE_C
#define GATE_C


#include "Gate.h"
#include "FlipFlop/FlipFlop.h"

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

Signal* Gate::getOutput()
{
	return this->output;
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

void Gate::addInput(std::string inputLabel) {
	this->inputs.push_back(Signal::getSignal(inputLabel));
}

void Gate::addInput(Signal* input) {
	this->inputs.push_back(input);
}

void Gate::removeInput(std::string inputLabel) {
	for (
		std::vector<Signal*>::iterator i = this->inputs.begin();
		i != this->inputs.end();
		i++
		) {
		if ((*i)->getLabel() == inputLabel) {
			this->inputs.erase(i);
			break;
		}
	}
}

void Gate::removeInput(Signal* input) {
	for (
		std::vector<Signal*>::iterator i = this->inputs.begin();
		i != this->inputs.end();
		i++
		) {
		if ((*i) == input) {
			this->inputs.erase(i);
			break;
		}
	}
}

std::vector<Signal*> Gate::getInputs()
{
	return this->inputs;
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
	bool somethingChanged, goAgain;
	FlipFlop* tmpFF;
	value_t prevVal;
	while (!Signal::allSignalsSet()) {
		somethingChanged = false;
		for (i = gates.begin(); i != gates.end(); i++) {
			if ((*i)->isReady() && (*i)->getOutputValue() == UNKNOWN_VALUE) { //is ready and output is unset
				prevVal = (*i)->getOutputValue();
				(*i)->setOutputValue();
				if ((*i)->getOutputValue() != prevVal) somethingChanged = true;
			}
		}
		if (!somethingChanged) {
			throw std::runtime_error("Unable to process all gates! There maybe some orphaned gates or signals.");
		}


		
		//if (Signal::allSignalsSet()) {
		//	do {
		//		goAgain = false;
		//		for (i = gates.begin(); i != gates.end(); i++) {
		//			if (((*i)->isReady() == false && (*i)->getOutputValue() != UNKNOWN_VALUE) || (*i)->getOutputValue() != (*i)->calculateValue()) {
		//				(*i)->getOutput()->setValue(UNKNOWN_VALUE);
		//				goAgain = true;
		//			} 
		//		}
		//	} while (goAgain);
		//}
	}

	for (i = gates.begin(); i != gates.end(); i++) {
		tmpFF = dynamic_cast<FlipFlop*>(*i);
		if (tmpFF) {
			tmpFF->save();
		}
	}
}

std::string Gate::getLabel() {
	return this->label;
}

int Gate::countFlipFlops() {
	int count = 0;
	for (std::vector<Gate*>::iterator i = gates.begin(); i != gates.end(); i++)	{
		if (dynamic_cast<FlipFlop*>(*i)) count++;
	}
	return count;
}

Gate* Gate::getGateByLabel(std::string label) {
	std::vector<Gate*>::iterator i = gates.begin();
	while (i != gates.end()) {
		if ((*i)->getLabel() == label) return (*i);
		i++;
	}
	throw std::runtime_error("Gate " + label + " not found!");
}

void Gate::reset() {
	this->getOutput()->setValue(UNKNOWN_VALUE);
}

void Gate::resetAll() {
	for(std::vector<Gate*>::iterator i = gates.begin(); i != gates.end(); i++) {
		(*i)->reset();
	}
}

#endif