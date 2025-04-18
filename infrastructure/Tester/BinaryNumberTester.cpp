#ifndef BINTESTER_C
#define BINTESTER_C

#include "BinaryNumberTester.h"

BinaryNumberTester::BinaryNumberTester() : Tester() {
	
}

std::vector<value_t> BinaryNumberTester::getNextTestVector() {
	if (testVectors.empty()) generateTestVectors();
	return Tester::getNextTestVector();
}

std::vector<std::vector<value_t>> BinaryNumberTester::getTestVectors() {
	if (testVectors.empty()) generateTestVectors();
	return Tester::getTestVectors();
}

bool BinaryNumberTester::endOfTestVectors() {
	if (testVectors.empty()) generateTestVectors();
	return Tester::endOfTestVectors();
}

void BinaryNumberTester::restartIterator() {
	if (testVectors.empty()) generateTestVectors();
	Tester::restartIterator();
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
	currentTestVector = testVectors.begin();
}



#endif