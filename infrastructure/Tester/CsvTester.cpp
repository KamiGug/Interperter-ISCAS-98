#ifndef CSVTESTER_C
#define CSVTESTER_C

#include "CsvTester.h"

CsvTester::CsvTester(std::string filename) {
	this->separator = ',';
	this->filename = filename;
	generateTestVectors(filename);
	currentTestVector = testVectors.begin();
}

void CsvTester::generateTestVectors(std::string filename) {
	std::ifstream file(this->filename);
	std::string tmp;
	
	std::vector<value_t> values;

	while (std::getline(file, tmp)) {
		std::stringstream line(tmp);
		values.clear();
		while (std::getline(line, tmp, this->separator))
		{
			values.push_back(getValueString(tmp));
		}
		testVectors.push_back(values);
	}
	file.close();
}



#endif