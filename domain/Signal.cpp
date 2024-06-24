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

Signal::Signal(std::string label, value_t value) {
	this->isOutput = false;
	this->setValue(value);
	this->label = label;
}


std::vector<Signal*> Signal::signals;
std::vector<Signal*> Signal::inputs;
std::vector<Signal*> Signal::outputs;

void Signal::addSignal(std::string label, value_t value, bool isOutput, bool isInput) {
	Signal* tmp = new Signal(label, value);
	signals.push_back(tmp);
	if (isInput) inputs.push_back(tmp);
	if (isOutput) outputs.push_back(tmp);
}

Signal* Signal::getSignal(std::string label, value_t valueToSetIfNonexistent) {
	std::vector<Signal*>::iterator i = signals.begin();
	while (i != signals.end()) {
		if ((*i)->getLabel() == label) return (*i);
		i++;
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

#endif