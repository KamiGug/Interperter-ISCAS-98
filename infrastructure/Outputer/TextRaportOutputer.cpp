#ifndef TEXT_RAPORT_OUTPUTER_C
#define TEXT_RAPORT_OUTPUTER_C

#include "TextRaportOutputer.h"

TextRaportOutputer::~TextRaportOutputer() {

}

void TextRaportOutputer::generateOutput(std::vector<Results_t*> result)
{
	setNoFaultOutputs(result);
	int countOfCoveredFaults = 0;
	std::vector<Fault*> listOfFaults = getListOfFaults(result);
	std::vector<Fault*>::iterator i = listOfFaults.begin();
	
	if (listOfFaults.size() == 0) {
		overAllOutput << "No faults were tested. Did you mean to use another outputer?";
	}
	else {
		std::vector<Results_t*> listOfCoveringTestVectors;
		std::vector<Signal*>::iterator itTestVector;
		for (std::vector<Fault*>::iterator i = listOfFaults.begin(); i != listOfFaults.end(); i++) {
			listOfCoveringTestVectors.push_back(coversFault((*i), result));
			if (listOfCoveringTestVectors.back() == nullptr) {
				eachFaultOutput << "No test covers fault " << (*i)->getDescription() << std::endl;
			}
			else {
				countOfCoveredFaults++;
				eachFaultOutput << "Fault " << (*i)->getDescription() << " is covered by test vector: " << std::endl;
				for (
					itTestVector = listOfCoveringTestVectors.back()->inputs.begin();
					itTestVector != listOfCoveringTestVectors.back()->inputs.end();
					itTestVector++
					) {
					eachFaultOutput << (*itTestVector)->getLabel() << ": " << ((*itTestVector)->getValue() == LOW_LEVEL ? "low" : "high");
					if (itTestVector + 1 != listOfCoveringTestVectors.back()->inputs.end()) {
						eachFaultOutput << ", ";
					}
				}
				eachFaultOutput << std::endl;
			}
		}
		overAllOutput << "The passed test vectors cover "
			<< countOfCoveredFaults
			<< "/"
			<< listOfFaults.size()
			<< ". That is about "
			<< (countOfCoveredFaults * 100) / listOfFaults.size()
			<< "%.";
	}
	

	
	if (this->shouldPrint) outputToStdout();
	if (this->shouldSaveToFile) saveOutputToFile();
}

void TextRaportOutputer::saveOutputToFile() {
	std::fstream file(this->filename, std::fstream::out);
	std::string tmp;
	while (std::getline(this->overAllOutput, tmp)) {
		file << tmp << '\n';
	}
	while (std::getline(this->eachFaultOutput, tmp)) {
		file << tmp << '\n';
	}
	file << std::flush;
	file.close();
}

void TextRaportOutputer::outputToStdout() {
	std::string tmp;
	while (std::getline(this->overAllOutput, tmp)) {
		std::cout << tmp << std::endl;
	}
	while (std::getline(this->eachFaultOutput, tmp)) {
		std::cout << tmp << std::endl;
	}
}

Results_t* TextRaportOutputer::coversFault(Fault* fault, std::vector<Results_t*> results) {
	//std::vector<Results_t*> testsWithFault;
	std::vector<Signal*>::iterator itIn_NoFault, itIn_Faulty;
	std::vector<Subresults_t*>::iterator itOut_NoFault, itOut_Faulty;
	Results_t* candidate;
	bool isTheTest;
	
	for (std::vector<Results_t*>::iterator currResult = results.begin(); currResult != results.end(); currResult++) {
		if ((*currResult)->fault != nullptr
			&& (*currResult)->fault->getDescription() == fault->getDescription()
			&& (*currResult)->fault->getType() == fault->getType()
			) {
			isTheTest = false;

			candidate = getNoFaultResultWithMatchingTestVector((*currResult));


			//iterate over clockIntervals
			itOut_NoFault = candidate->clockIntervals.begin();
			itOut_Faulty = (*currResult)->clockIntervals.begin();
			while (
				!isTheTest
				&& itOut_NoFault != candidate->clockIntervals.end() 
				&& itOut_Faulty != (*currResult)->clockIntervals.end()
			) {

				itIn_NoFault = (*itOut_NoFault)->outputs.begin();
				itIn_Faulty = (*itOut_Faulty)->outputs.begin();
				//iterate over outputs
				while (itIn_NoFault != (*itOut_NoFault)->outputs.end()
					&& itIn_Faulty != (*itOut_Faulty)->outputs.end()
				) {
					if ((*itIn_NoFault)->getValue() != (*itIn_Faulty)->getValue()) {
						isTheTest = true;
						break;
					}
					itIn_NoFault++;
					itIn_Faulty++;
				}
				itOut_NoFault++;
				itOut_Faulty++;
			}
			if (isTheTest) {
				return *currResult;
			}
		}
	}
	return nullptr;
}

void TextRaportOutputer::setNoFaultOutputs(std::vector<Results_t*> results) {
	noFaultOutputs.clear();
	for (std::vector<Results_t*>::iterator currResult = results.begin(); currResult != results.end(); currResult++) {
		if ((*currResult)->fault == nullptr) {
			noFaultOutputs.push_back(*currResult);
		}
	}
	if (noFaultOutputs.empty()) throw std::runtime_error("Tests were not made without a gate fault!");
}

std::vector<Fault*> TextRaportOutputer::getListOfFaults(std::vector<Results_t*> results) {
	std::vector<Fault*> result;
	std::vector<Fault*>::iterator backIt;
	bool isNotInAlready;
	for (std::vector<Results_t*>::iterator currResult = results.begin(); currResult != results.end(); currResult++) {
		if ((*currResult)->fault != nullptr && (*currResult)->fault->getType() != UNKNOWN_VALUE) {
			isNotInAlready = true;
			for (backIt = result.begin(); backIt != result.end(); backIt++) {
				if ((*currResult)->fault->getDescription() == (*backIt)->getDescription() && (*currResult)->fault->getType() == (*backIt)->getType()) {
					isNotInAlready = false;
					break;
				}
			}
			if (isNotInAlready) {
				result.push_back((*currResult)->fault);
			}
		}
	}
	return result;
}

Results_t* TextRaportOutputer::getNoFaultResultWithMatchingTestVector(Results_t* toMatch) {
	bool isOk; std::vector<Signal*>::iterator itNoFault, itFaulty;
	for (std::vector<Results_t*>::iterator currResult = noFaultOutputs.begin(); currResult != noFaultOutputs.end(); currResult++) {
		isOk = true;
		itNoFault = (*currResult)->inputs.begin();
		itFaulty = toMatch->inputs.begin();
		while (itNoFault != (*currResult)->inputs.end() && itFaulty != toMatch->inputs.end()) {
			if ((*itNoFault)->getValue() != (*itFaulty)->getValue()) {
				isOk = false;
				break;
			}
			itNoFault++; 
			itFaulty++;
		}
		if (isOk) {
			return *currResult;
		}
	}
	throw std::runtime_error(
		"Unable to find a matching test vector that does not have a fault!"
	);
}




#endif


