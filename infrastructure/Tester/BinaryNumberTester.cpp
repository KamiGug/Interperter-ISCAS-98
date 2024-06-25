#ifndef BINTESTER_C
#define BINTESTER_C

#include "BinaryNumberTester.h"

BinaryNumberTester::BinaryNumberTester() : Tester() {
	generateTestVectors();
	currentTestVector = testVectors.begin();
}

void BinaryNumberTester::generateTestVectors() {
	int numberOfInputs = Signal::getInputs().size();
	unsigned int mask = 1;
	std::vector<value_t>* tmp;
	for (unsigned val = 0; val < power(2, numberOfInputs); val++) {
		testVectors.push_back(std::vector<value_t>());
		tmp = &(testVectors.back());
		for (int i = numberOfInputs - 1; i >= 0; i--) {
			tmp->push_back((val & (mask << i)) ? HIGH_LEVEL : LOW_LEVEL);
			//Signal::getSignal(inputs[i])->setValue((val & (mask << i)) ? HIGH_LEVEL : LOW_LEVEL);
		}
	}
}



#endif