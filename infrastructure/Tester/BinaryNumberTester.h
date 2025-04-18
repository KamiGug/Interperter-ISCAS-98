#ifndef BINTESTER_H
#define BINTESTER_H

#include "Tester.h"
#include "../../helpers/misc.h"

class BinaryNumberTester : public Tester {
public:
	BinaryNumberTester();
	virtual std::vector<value_t> getNextTestVector();
	virtual std::vector<std::vector<value_t>> getTestVectors();
	virtual bool endOfTestVectors();
	void restartIterator();

protected:
	virtual void generateTestVectors();
};

#endif