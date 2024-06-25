#ifndef BINTESTER_H
#define BINTESTER_H

#include "Tester.h"
#include "../../helpers/misc.h"

class BinaryNumberTester : public Tester {
public:
	BinaryNumberTester();


protected:
	virtual void generateTestVectors();
};

#endif