#ifndef CSV_IN_OUTPUTER_C
#define CSV_IN_OUTPUTER_C

#include "CsvInputOutputer.h"

CsvInputOutputer::~CsvInputOutputer() {

}

void CsvInputOutputer::generateOutput(std::vector<Results_t*> result)
{
	std::vector<std::vector<Signal*>> listOfInputs = getListOfInputs(result);
	std::vector<Results_t*> matchedResults;
	std::vector<Results_t*>::iterator matchedResult;
	std::vector<Signal*>::iterator signalIterator;
	std::vector<Subresults_t*>::iterator outputIterator;
	bool needsClock = false;
	for (std::vector<std::vector<Signal*>>::iterator i = listOfInputs.begin(); i != listOfInputs.end(); i++) {
		output.push_back(",input:");
		output.push_back("");
		matchedResults = getListOfResultsWithTestVector(result, *i);
		matchedResult = matchedResults.begin();
		if (matchedResult == matchedResults.end()) continue;
		if ((*matchedResult)->clockIntervals.size() > 1) needsClock = true;
		for (signalIterator = (*matchedResult)->inputs.begin(); signalIterator != (*matchedResult)->inputs.end(); signalIterator++) {
			output.back().append("," + getValueNumberAsString((*signalIterator)->getValue()));
		}
		if (needsClock) {
			output.push_back("clk,outputs:");
			for (; matchedResult != matchedResults.end(); matchedResult++) {
				output.push_back("," +
					(
						(*matchedResult)->fault != nullptr
						&& (*matchedResult)->fault->getType() != UNKNOWN_VALUE
						? (*matchedResult)->fault->getDescription()
						: "No fault"
						)
				);
				for (outputIterator = (*matchedResult)->clockIntervals.begin(); outputIterator != (*matchedResult)->clockIntervals.end(); outputIterator++) {
					output.push_back(getValueNumberAsString((*outputIterator)->clock));
					for (signalIterator = (*outputIterator)->outputs.begin(); signalIterator != (*outputIterator)->outputs.end(); signalIterator++) {
						output.back().append("," + getValueNumberAsString((*signalIterator)->getValue()));
					}
				}
			}
		
		}
		else {
			output.push_back("fault,outputs:");
			for (; matchedResult != matchedResults.end(); matchedResult++) {
				output.push_back(
					(
						(*matchedResult)->fault != nullptr
						&& (*matchedResult)->fault->getType() != UNKNOWN_VALUE
						? (*matchedResult)->fault->getDescription()
						: "No fault"
						)
				);
				for (signalIterator = (*matchedResult)->clockIntervals[0]->outputs.begin(); signalIterator !=(*matchedResult)->clockIntervals[0]->outputs.end(); signalIterator++) {
					output.back().append("," + getValueNumberAsString((*signalIterator)->getValue()));
				}
			}
		}
		output.push_back("");
	}
	normalizeCommasInOutput();
	if (this->shouldPrint) outputToStdout();
	if (this->shouldSaveToFile) saveOutputToFile();
}

void CsvInputOutputer::saveOutputToFile() {
	std::ofstream file(this->filename, std::fstream::out);
	for (std::vector<std::string>::iterator it = output.begin(); it != output.end(); it++) {
		file << *it << '\n';
	}
	file << std::flush;
	file.close();
}

void CsvInputOutputer::outputToStdout() {
	for (std::vector<std::string>::iterator it = output.begin(); it != output.end(); it++) {
		std::cout << *it << std::endl;
	}
}

std::vector<std::vector<Signal*>> CsvInputOutputer::getListOfInputs(std::vector<Results_t*> results) {
	std::vector < std::vector<Signal*>> result;
	std::vector < std::vector<Signal*>>::iterator savedInputs;
	std::vector<Signal*>::iterator itAlreadySaved, itCurrResult;
	bool isNotInAlready;

	std::vector<Results_t*>::iterator currResult = results.begin();
	if (currResult == results.end()) return result;
	result.push_back((*currResult)->inputs);
	currResult++;
	for (; currResult != results.end(); currResult++) {
		isNotInAlready = true;
		savedInputs = result.begin();
		while (isNotInAlready && savedInputs != result.end()) {
			isNotInAlready = false;
			itAlreadySaved = (*currResult)->inputs.begin();
			itCurrResult = savedInputs->begin();
			while (
				itAlreadySaved != (*currResult)->inputs.end()
				&& itCurrResult != savedInputs->end()
				) {
				if ((*itAlreadySaved)->getValue() != (*itCurrResult)->getValue()) {
					isNotInAlready = true;
					break;
				}
				itAlreadySaved++;
				itCurrResult++;
			}
			savedInputs++;
		}
		
		
		if (isNotInAlready) {
			result.push_back((*currResult)->inputs);
		}

	}
	return result;
}

std::vector<Results_t*> CsvInputOutputer::getListOfResultsWithTestVector(std::vector<Results_t*> results, std::vector<Signal*> input) {
	std::vector<Results_t*> result;
	bool isOk;
	std::vector<Signal*>::iterator correctTestVectorIterator, allResultsSignalIterator;
	for (std::vector<Results_t*>::iterator currResult = results.begin(); currResult != results.end(); currResult++) {
		isOk = true;
		allResultsSignalIterator = (*currResult)->inputs.begin();
		correctTestVectorIterator = input.begin();
		while (allResultsSignalIterator != (*currResult)->inputs.end() && correctTestVectorIterator != input.end()) {
			if ((*allResultsSignalIterator)->getValue() != (*correctTestVectorIterator)->getValue()) {
				isOk = false;
				break;
			}
			allResultsSignalIterator++;
			correctTestVectorIterator++;
		}
		if (isOk) {
			result.push_back(*currResult);
		}
	}
	return result;
}

void CsvInputOutputer::normalizeCommasInOutput() {
	std::vector<std::string>::iterator it;
	int max_commas = 0, count = 0;
	for (it = output.begin(); it != output.end(); it++) {
		count = countCharacter(*it, ',');
		if (count > max_commas) max_commas = count;
	}

	for (it = output.begin(); it != output.end(); it++) {
		count = max_commas - countCharacter(*it, ',');
		for (int i = 0; i < count; i++) {
			it->append(",");
		}
	}
}


#endif


