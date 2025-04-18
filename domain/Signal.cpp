#ifndef SIGNAL_C
#define SIGNAL_C

#include "Signal.h"

std::string Signal::getLabel() {
	return this->label;
}

value_t Signal::getValue() {
	return this->value;
}

void Signal::setValue(value_t value) {
	this->value = value;
}

void Signal::setOutput() {
	if (this->isOutput) throw std::runtime_error("The same signal is used as output twice!");
	this->isOutput = true;
}

void Signal::unsetOutput() {
	this->isOutput = false;
}

Signal::Signal(std::string label, value_t value, bool isOutput) {
	this->isOutput = isOutput;
	this->setValue(value);
	this->label = label;
}

Signal::Signal(Signal* signalToCopy) {
	this->value = signalToCopy->value;
	this->label = signalToCopy->label;
	this->isOutput = signalToCopy->isOutput;
}

void Signal::tickClock() {
	if (clock->value == LOW_LEVEL) clock->value = HIGH_LEVEL;
	else clock->value = LOW_LEVEL;
}

Signal* Signal::getClock() {
	return clock;
}

void Signal::setClock(value_t value) {
	if (clock->value == UNKNOWN_VALUE) tickClock();
	else clock->value = value;
}


std::vector<Signal*> Signal::signals;
std::vector<Signal*> Signal::inputs;
std::vector<Signal*> Signal::outputs;

std::vector<Signal*> Signal::constSignals = 
{ 
	new Signal("high", HIGH_LEVEL, true), 
	new Signal("low", LOW_LEVEL, true)
};

Signal* Signal::clock = new Signal("CLOCK", HIGH_LEVEL, true);

void Signal::addSignal(std::string label, value_t value, bool isOutput, bool isInput) {
	Signal* tmp = new Signal(label, value);
	signals.push_back(tmp);
	if (isInput) inputs.push_back(tmp);
	if (isOutput) outputs.push_back(tmp);
}

Signal* Signal::getSignal(std::string label, value_t valueToSetIfNonexistent) {
	if (label == "high" || label == "low") {
		for (
			std::vector<Signal*>::iterator i = constSignals.begin(); 
			i != constSignals.end(); 
			i++
		) {
			if ((*i)->getLabel() == label) return (*i);
		}
	}

	std::vector<Signal*>::iterator i = signals.begin();
	for (
		std::vector<Signal*>::iterator i = signals.begin();
		i != signals.end();
		i++
	) {
		if ((*i)->getLabel() == label) return (*i);
	}
	signals.push_back(new Signal(label, valueToSetIfNonexistent));
	return signals.back();
}

std::vector<Signal*> Signal::buildFromLabels(std::vector<std::string> labels) {
	std::vector<std::string>::iterator itLabels = labels.begin();
	std::vector<Signal*> result;
	while (itLabels != labels.end()) {
		result.push_back(Signal::getSignal(*itLabels));
		itLabels++;
	}
	return result;
}

void Signal::setSignalAsInputOrOutput(std::string label, bool isOutput, value_t value) {
	std::vector<Signal*>::iterator i = signals.begin();
	while (i != signals.end()) {
		if ((*i)->getLabel() == label) break;
		i++;
	}
	if (i == signals.end()) {
		Signal::addSignal(label, value, isOutput, !isOutput);
	}
	else {
		if (isOutput) outputs.push_back(*i);
		else inputs.push_back(*i);
	}
}

bool Signal::allSignalsSet() {
	std::vector<Signal*>::iterator i = signals.begin();
	while (i != signals.end()) {
		if ((*i)->getValue() == UNKNOWN_VALUE) return false;
		i++;
	}
	return true;
}

void Signal::unsetAllSignals() {
	std::vector<Signal*>::iterator i = signals.begin();
	while (i != signals.end()) {
		(*i)->setValue(UNKNOWN_VALUE);
		i++;
	}
}

int Signal::countInput() {
	return inputs.size();
}

int Signal::countOutput() {
	return outputs.size();
}

void Signal::setInputs(std::vector<value_t> values) {
	if (values.size() != inputs.size()) {
		throw std::runtime_error(
			"Test vector size mismatch! Test vector size = "
			+ std::to_string(values.size())
			+ ", Input vector size = "
			+ std::to_string(inputs.size())
			+ "."
		);
	}
	int size = values.size();
	for (int i = 0; i < size; i++) {
		inputs[i]->setValue(values[i]);
	}
}

std::vector<Signal *> Signal::getInputs() {
	return inputs;
}

std::vector<Signal*> Signal::getOutputs() {
	return outputs;
}

#endif