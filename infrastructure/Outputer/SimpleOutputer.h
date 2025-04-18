#ifndef SIMPLE_OUTPUTER_H
#define SIMPLE_OUTPUTER_H

#include <sstream>

#include "Outputer.h"
#include "../../helpers/misc.h"

class SimpleOutputer: public Outputer {
public:
	SimpleOutputer(std::string filename = "", bool shouldPrint = true, bool shouldSaveToFile = false) : Outputer(filename, shouldPrint, shouldSaveToFile) {

	}
	~SimpleOutputer();
	virtual void generateOutput(std::vector<Results_t*>);
	virtual void saveOutputToFile();
	virtual void outputToStdout();

protected:

private:
	std::stringstream output;
};



#endif