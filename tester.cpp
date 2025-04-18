// tester.cpp : Defines the entry point for the application.
//

#include "tester.h"

using namespace std;

int main(int argc, char* argv[])
{
	Tester* tester = nullptr;
	Outputer* outputer = nullptr;
	std::string iscasFile, ftlFile;
	parseArgs(argc, argv, tester, outputer, iscasFile, ftlFile);

	//R"(C:\Users\gugka\Documents\US\rok2\architektura-systemów-komputerowych\cpp\tester\iscas-test-dff.txt)"
	
	#ifdef DEBUG
		iscasFile = R"(C:\Users\gugka\Documents\US\rok2\architektura-systemów-komputerowych\cpp\tester\iscas-test-dff.txt)";
		ftlFile = R"(C:\Users\gugka\Documents\US\rok2\architektura-systemów-komputerowych\cpp\tester\ftl-test-dff.ftl)";
		//ftlFile = "";
		delete outputer;
		//outputer = new SimpleOutputer();
		outputer = new CsvInputOutputer();
		//outputer = new TextRaportOutputer();
		//outputer->setFilename(R"(C:\Users\gugka\Documents\US\rok2\architektura-systemów-komputerowych\cpp\tester\test.txt)");
		//outputer->setShouldSaveToFile(true);
		//outputer->setShouldPrint(false);
		delete tester;
		tester = new BinaryNumberTester();

	#endif // DEBUG
	
	//iscasFile = "idontexistlikeatall";
	Interpreter interpreter(iscasFile);
	interpreter.interpret();

	//Tester* tester = new BinaryNumberTester();
	//Tester* tester = new CsvTester(R"(C:\Users\gugka\Documents\US\rok2\architektura-systemów-komputerowych\cpp\tester\csvtest.txt)");
	//Outputer* outputer = new SimpleOutputer();
	//Outputer* outputer = new TextRaportOutputer();

	//R"(C:\Users\gugka\Documents\US\rok2\architektura-systemów-komputerowych\cpp\tester\ftl-test-dff.ftl)"
	//ftlFile = "";
	FaultReader faultReader(ftlFile);

	std::vector<Fault*> faults = faultReader.getFaults();
	Simulator simulator(tester, faults);
	simulator.runAllTests();

	outputer->generateOutput(simulator.getResults());

	delete tester;
	delete outputer;

	return 0;
}
