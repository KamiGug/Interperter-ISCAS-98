#ifndef OUTPUTER_H
#define OUTPUTER_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "../../domain/Signal.h"
#include "../../domain/Fault/Fault.h"

#include "../../domain/Results.h"

class Outputer {
public:
	Outputer(std::string filename = "", bool shouldPrint = true, bool shouldSaveToFile = false);
	~Outputer();
	virtual void generateOutput(std::vector<Results_t*> results) = 0;
	virtual void saveOutputToFile() = 0;
	virtual void outputToStdout() = 0;
	void setShouldPrint(bool shouldPrint);
	void setShouldSaveToFile(bool shouldSaveToFile);
	void setFilename(std::string filename);

protected:
	std::string filename;
	bool shouldPrint;
	bool shouldSaveToFile;

private:
	
	
};



#endif