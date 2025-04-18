#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <vector>
#include <exception>


#include "../domain/Signal.h"
#include "../domain/Results.h"
#include "../domain/Fault/Fault.h"
#include "../infrastructure/Tester/Tester.h"
#include "../infrastructure/Tester/CsvTester.h"
#include "../infrastructure/Tester/BinaryNumberTester.h"


class Simulator {
public:
	Simulator(Tester* tester, std::vector<Fault*> faults);
	~Simulator();
	void runSingleTest(Fault* fault = nullptr);
	void runAllTests();
	std::vector<Results_t *> getResults();
	void restartFaultPointer();

protected:



private:
	Tester* tester;
	std::vector<Results_t *> results;
	std::vector<Fault *> faults;
	std::vector<Fault*>::iterator currentFault;
};



#endif