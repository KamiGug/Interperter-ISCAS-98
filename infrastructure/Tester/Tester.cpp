#ifndef TESTER_C
#define TESTER_C

#include "Tester.h"

Tester::Tester() {
	currentTestVector = testVectors.begin();
}

Tester ::~Tester() {

}

std::vector<value_t> Tester::getNextTestVector() {
	if (endOfTestVectors()) throw std::runtime_error("Tried to get a test vector when there are none!");
	return (*(currentTestVector++));
}

std::vector<std::vector<value_t>> Tester::getTestVectors() {
	return testVectors;
}

bool Tester::endOfTestVectors() {
	return currentTestVector == testVectors.end();
}

#endif