#ifndef CSV_IN_OUTPUTER_H
#define CSV_IN_OUTPUTER_H

#include "Outputer.h"
#include "../../helpers/misc.h"

class CsvInputOutputer : public Outputer {
public:
	CsvInputOutputer(std::string filename = "", bool shouldPrint = true, bool shouldSaveToFile = false) : Outputer(filename, shouldPrint, shouldSaveToFile) {

	}
	~CsvInputOutputer();
	virtual void generateOutput(std::vector<Results_t*>);
	virtual void saveOutputToFile();
	virtual void outputToStdout();

protected:

private:
	char separator = ',';
	std::vector<std::string> output;
	std::vector<std::vector<Signal*>> getListOfInputs(std::vector<Results_t*> results);
	std::vector<Results_t*> getListOfResultsWithTestVector(std::vector<Results_t*> results, std::vector<Signal*> input);
	void normalizeCommasInOutput();
};



#endif