#ifndef SIMPLE_OUTPUTER_C
#define SIMPLE_OUTPUTER_C

#include "SimpleOutputer.h"

SimpleOutputer::~SimpleOutputer() {

}

void SimpleOutputer::generateOutput(std::vector<Results_t*> result)
{
	std::vector<Signal*>::iterator i;
	std::vector<Subresults_t*>::iterator i_sub;
	this->output.clear();
	for (std::vector<Results_t*>::iterator currResult = result.begin(); currResult < result.end(); currResult++) {
		if ((*currResult)->fault != nullptr && (*currResult)->fault->getType() != UNKNOWN_VALUE) {
			this->output << "FAULT AT GATE " << (*currResult)->fault->getDescription() << " of type "
				<< ((*currResult)->fault->getType() == LOW_LEVEL ? "stuck-at-0" : "stuck-at-1") << std::endl;
		}
		else {
			this->output << "No faults!" << std::endl;
		}

		if (!(*currResult)->inputs.empty()) {
			for (i = (*currResult)->inputs.begin(); i != (*currResult)->inputs.end(); i++) {
				this->output << "|" << (*i)->getLabel() << "=" << getValueName((*i)->getValue());
			}
			this->output << "|" << std::endl;
		}
		else {
			this->output << "No inputs were specified!" << std::endl;
		}

		for (i_sub = (*currResult)->clockIntervals.begin(); i_sub != (*currResult)->clockIntervals.end(); i_sub++) {
			this->output << "Clock set to " << ((*i_sub)->clock == LOW_LEVEL ? "low" : "high") << " level" << std::endl;
			for (i = (*i_sub)->outputs.begin(); i != (*i_sub)->outputs.end(); i++) {
				this->output << (*i)->getLabel() << ": " << getValueName((*i)->getValue()) << std::endl;
			}
			this->output << "-------------------------------------------------------------------------------" << std::endl;
		}
		
	}
	if (this->shouldPrint) outputToStdout();
	if (this->shouldSaveToFile) saveOutputToFile();
}

void SimpleOutputer::saveOutputToFile() {
	std::fstream file(this->filename, std::fstream::out);
	std::string tmp;
	while (std::getline(this->output, tmp)) {
		file << tmp << '\n';
	}
	file << std::flush;
	file.close();
}

void SimpleOutputer::outputToStdout() {
	std::string tmp;
	while (std::getline(this->output, tmp)) {
		std::cout << tmp << std::endl;
	}
}


#endif

