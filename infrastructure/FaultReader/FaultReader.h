#ifndef FAULTREADER_H
#define FAULTREADER_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>

#include "../../domain/Fault/Fault.h"
#include "../../helpers/misc.h"
#include "../../domain/Fault/DoubleGateFault.h"
#include "../../domain/Fault/SingleGateFault.h"

class FaultReader {
public:
	FaultReader(std::string filename = "");
	~FaultReader();
	std::vector<Fault*> getFaults();

protected:

private:
	std::vector<Fault*> faults;
	void readFile(std::string filename);
};


#endif