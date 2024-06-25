#ifndef TESTER_H
#define TESTER_H

#include <string>
#include <vector>
#include <stdexcept>

#include "../../domain/Value.h"
#include "../../domain/Signal.h"

class Tester {
public:
	Tester ();
	~Tester ();
	virtual std::vector<value_t> getNextTestVector();
	virtual bool endOfTestVectors();
	std::vector<std::vector<value_t>> getTestVectors();

protected:
	std::vector<std::vector<value_t>> testVectors;
	std::vector<std::vector<value_t>>::iterator currentTestVector;



private:

};



#endif