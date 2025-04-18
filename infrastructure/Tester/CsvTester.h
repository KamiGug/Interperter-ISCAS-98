#ifndef CSVTESTER_H
#define CSVTESTER_H

#include <string>
#include <iostream>
#include <regex>
#include <fstream>
#include <sstream>
#include <vector>
#include <exception>

#include "Tester.h"
#include "../../helpers/misc.h"

class CsvTester : public Tester {
public:
	CsvTester(std::string filename);


protected:
	virtual void generateTestVectors(std::string filename);

private:
	std::string filename;
	char separator;
};
#endif