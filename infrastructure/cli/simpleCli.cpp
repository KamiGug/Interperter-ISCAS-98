#ifndef SIMPLECLI_C
#define SIMPLECLI_C

#include "simpleCli.h"



void parseArgs(
	int argc, 
	char* argv[], 
	Tester*& tester, 
	Outputer*& outputer,
	std::string& iscas, 
	std::string& ftl
) {
	std::vector<std::string> args;
	std::string outputerFilename = "";
	bool iscasFilled = false, ftlFilled = false, outputToFile = false, OutputToStdout = false;
	//std::vector<std::string> args, Tester*& tester, Outputer*& outputer, bool& outputToFile, bool& OutputToStdout
	std::map < char, std::function<void(std::vector<std::string>::iterator i)>> switchMap = {
		{
			'f',[&](std::vector<std::string>::iterator i) {
				if (++i == args.end()) return;
				outputerFilename = *i;
				outputToFile = true;
			}
		}, {
			'o',[&](std::vector<std::string>::iterator i) {
				OutputToStdout = true;
			}
		}, {
			't',[&](std::vector<std::string>::iterator i) {
				if (outputer) delete outputer;
				outputer = new TextRaportOutputer();
			}
		}, {
			'g',[&](std::vector<std::string>::iterator i) {
				//if (outputer) delete outputer;
				//outputer = new CsvFaultGroupOutputer();
			}
		}, {
			'i',[&](std::vector<std::string>::iterator i) {
				if (outputer) delete outputer;
				outputer = new CsvInputOutputer();
			}
		}, {
			's',[&](std::vector<std::string>::iterator i) {
				if (outputer) delete outputer;
				outputer = new SimpleOutputer();
			}
		}, {
			'b',[&](std::vector<std::string>::iterator i) {
				if (tester) delete tester;
				tester = new BinaryNumberTester();
			}
		}, {
			'c',[&](std::vector<std::string>::iterator i) {
				if (++i == args.end()) return;
				if (tester) delete tester;
				tester = new CsvTester(*i);
			}
		}
	};
	for (int i = 1; i < argc; i++) {
		args.push_back(argv[i]);
	}
	for (std::vector<std::string>::iterator i = args.begin(); i < args.end(); i++) {
		if (i->at(0) == '-') { //switch
			for (auto c : (*i).substr(1, std::string::npos)) switchMap[c](i);
		}
		else {
			if (!iscasFilled) {
				iscas = (*i);
				iscasFilled = true;
			}
			else if (!ftlFilled) {
				ftl = (*i);
				ftlFilled = true;
			}
		}
	}
	if (outputToFile) {
		outputer->setShouldSaveToFile(true);
		outputer->setFilename(outputerFilename);
		if (!OutputToStdout) {
			outputer->setShouldPrint(false);
		}
	}

	if (tester == nullptr) {
		tester = new BinaryNumberTester();
	}
	if (outputer == nullptr) {
		outputer = new SimpleOutputer();
	}
	if (!iscasFilled) {
		#ifndef DEBUG
			std::cerr << "No Iscas file has been input!";
			exit(10);
		#endif
	}
	if (!ftlFilled) {
		//ftl = iscas.substr(0, iscas.rfind('.')) + ".ftl";
		ftl = "";
	}
}



#endif