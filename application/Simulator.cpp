#ifndef SIMULATOR_C
#define SIMULATOR_C

#include "Simulator.h"

Simulator::Simulator(Tester* tester, std::vector<Fault*> faults) {
	this->tester = tester;
	this->faults.swap(faults);
	currentFault = faults.begin();
}

Simulator::~Simulator() {
	delete tester;
}

void Simulator::runSingleTest(Fault* fault) {
	try {
		Gate::resetAll();	//unsets noninput signals and resets all flipflop inner states to LOW_LEVEL
		std::vector<value_t> runInputs = this->tester->getNextTestVector();
		Signal::setClock(HIGH_LEVEL);
		int numberOfIterations = power(2, Gate::countFlipFlops());
		if (numberOfIterations > 1) numberOfIterations *= 2;
		Signal::setInputs(runInputs);
		results.push_back(new Results_t(fault, Signal::getInputs()));

		for (int i = 0; i < numberOfIterations; i++) {
			Signal::unsetAllSignals();
			Signal::setInputs(runInputs);
			//this line is in the for loop to make sure SingleGateFault->apply() works in each iteration 
			if (fault != nullptr) fault->apply();
			Gate::setOutputOfAllGates();
			results.back()->appendOutput(Signal::getOutputs(), Signal::getClock()->getValue());
			//this line is in the for loop to make sure SingleGateFault->apply() works in each iteration 
			if (fault != nullptr) fault->revert();
			Signal::tickClock();
		}
	}
	catch (std::exception e) {
		std::cerr << "Caught an error in simulation!" << std::endl << e.what();
	}
	
}

void Simulator::runAllTests() {
	while (tester->endOfTestVectors() == false) {
		runSingleTest();
	}
	for (std::vector<Fault*>::iterator i = faults.begin(); i != faults.end(); i++) {
		this->restartFaultPointer();
		this->tester->restartIterator();
		while (tester->endOfTestVectors() == false) {
			runSingleTest(*i);
		}
	}
}

std::vector<Results_t *> Simulator::getResults() {
	return results;
}

void Simulator::restartFaultPointer() {
	currentFault = faults.begin();
}

#endif


