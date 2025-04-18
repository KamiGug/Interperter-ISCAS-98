#ifndef TEXT_RAPORT_OUTPUTER_H
#define TEXT_RAPORT_OUTPUTER_H

#include <sstream>
#include "Outputer.h"

class TextRaportOutputer : public Outputer {
public:
	TextRaportOutputer(std::string filename = "", bool shouldPrint = true, bool shouldSaveToFile = false) : Outputer(filename, shouldPrint, shouldSaveToFile) {

	}
	~TextRaportOutputer();
	virtual void generateOutput(std::vector<Results_t*>);
	virtual void saveOutputToFile();
	virtual void outputToStdout();

protected:

private:
	std::stringstream overAllOutput;
	std::stringstream eachFaultOutput;

	std::vector<Results_t*> noFaultOutputs;
	Results_t* coversFault(Fault* fault, std::vector<Results_t*> result);

	void setNoFaultOutputs(std::vector<Results_t*> result);

	Results_t* getNoFaultResultWithMatchingTestVector(Results_t* toMatch);

	std::vector<Fault*> getListOfFaults(std::vector<Results_t*> results);

};



#endif