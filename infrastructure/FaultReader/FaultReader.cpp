
#ifndef FAULTREADER_C
#define FAULTREADER_C

#include "FaultReader.h"

FaultReader::FaultReader(std::string filename) {
	this->readFile(filename);
}

FaultReader::~FaultReader() {

}

void FaultReader::readFile(std::string filename) {
	try
	{
		std::ifstream file(filename);
		std::string line, tmpStr1, tmpStr2, tmpStr3;
		int tmpInt1, tmpInt2;
		std::smatch matches;
		while (std::getline(file, line)) {
			if (std::regex_search(line, matches, std::regex("^\\s*#.*$")) || std::regex_search(line, matches, std::regex("^\\s*$"))) {
				continue;
			}
			if (std::regex_match(line, matches, std::regex(R"(.*->.*)"))) {
				tmpInt1 = line.find('-');
				tmpStr1 = line.substr(0, tmpInt1);
				trim(tmpStr1);
				for (auto& c : tmpStr1) c = tolower(c);

				tmpInt1 += 2;
				tmpInt2 = line.find('/');
				tmpStr2 = line.substr(tmpInt1, tmpInt2 - tmpInt1);
				trim(tmpStr2);
				for (auto& c : tmpStr2) c = tolower(c);

				tmpInt1 = line.find('#');

				tmpStr3 = line.substr(++tmpInt2, tmpInt1 == std::string::npos ? tmpInt1 : tmpInt1 - tmpInt2);
				trim(tmpStr3);
				for (auto& c : tmpStr3) c = tolower(c);

				faults.push_back(new DoubleGateFault(tmpStr1, tmpStr2, getValueString(tmpStr3)));
			}
			else {
				tmpInt1 = line.find('/');
				tmpStr1 = line.substr(0, tmpInt1);
				trim(tmpStr1);
				for (auto& c : tmpStr1) c = tolower(c);

				tmpInt2 = line.find('#');

				tmpStr2 = line.substr(++tmpInt1, tmpInt2 == std::string::npos ? tmpInt2 : tmpInt2 - tmpInt1);
				trim(tmpStr2);
				for (auto& c : tmpStr2) c = tolower(c);
				faults.push_back(new SingleGateFault(tmpStr1, getValueString(tmpStr2)));
			}
		}
		file.close();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Caught an error while interpreting faults file!" << std::endl << e.what();
	}
}

std::vector<Fault*> FaultReader::getFaults() {
	return faults;
}





#endif


