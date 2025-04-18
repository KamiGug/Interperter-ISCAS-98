#ifndef OUTPUTER_C
#define OUTPUTER_C

#include "Outputer.h"

Outputer::Outputer(std::string filename, bool shouldPrint, bool shouldSaveToFile) {
	this->shouldPrint = shouldPrint;
	this->filename = filename;
	if (filename == "") {
		this->shouldSaveToFile = false;
	}
	else {
		this->shouldSaveToFile = shouldSaveToFile;
	}
}

Outputer::~Outputer() {

}

void Outputer::setShouldPrint(bool shouldPrint) {
	this->shouldPrint = shouldPrint;
}

void Outputer::setShouldSaveToFile(bool shouldSaveToFile) {
	this->shouldSaveToFile = shouldSaveToFile;
}

void Outputer::setFilename(std::string filename) {
	this->filename = filename;
}


#endif

