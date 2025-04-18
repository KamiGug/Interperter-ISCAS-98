#ifndef INTERPRETER_C
#define INTERPRETER_C

#include "Interpreter.h"


Interpreter::Interpreter(std::string filename) {
	this->filename = filename;
}

Interpreter::~Interpreter() {

}

void Interpreter::interpret() {
	try
	{
		std::ifstream file(this->filename);
		if (!file) throw std::runtime_error("No such file " + this->filename);
		std::string line, output, type, clk;
		std::vector<std::string> inputs;
		const std::regex commentAtStartRegex("^\\s*#.*$");
		const std::regex emptyRegex("^\\s*$");
		int tmpInt1, tmpInt2;
		gateFactory_t* gateFactory = initGateFactory();


		const std::regex hasEqualSignRegex("^.+=[^=]+$");
		std::smatch matches;
		while (getline(file, line)) {
			if (std::regex_search(line, matches, commentAtStartRegex) || std::regex_search(line, matches, emptyRegex)) {
				continue;
			}
			inputs.clear();
			clk = "";
			if (std::regex_match(line, matches, hasEqualSignRegex)) {
				//here is a gate

				tmpInt1 = line.find('=');
				output = line.substr(0, tmpInt1);
				trim(output);
				for (auto& c : output) c = tolower(c);

				tmpInt1++;
				tmpInt2 = line.find('(');
				type = line.substr(tmpInt1, tmpInt2 - tmpInt1);
				trim(type);
				for (auto& c : type) c = tolower(c);

				tmpInt2++;
				line = line.substr(tmpInt2, line.find(")") - tmpInt2);
				for (auto& c : line) c = tolower(c);
				std::stringstream test(line);
				while (std::getline(test, line, ','))
				{
					trim(line);
					if (std::regex_match(line, matches, std::regex(R"(.*clk:.*)"))) {
						clk = line.substr(line.find(':') + 1, std::string::npos);
					}
					else {
						inputs.push_back(line);
					}


				}
				Gate::appendGate((*gateFactory)[type](inputs, output, clk));

			}
			else {
				//here is an input or output setter

				tmpInt1 = line.find('(');
				type = line.substr(0, tmpInt1);
				trim(type);
				for (auto& c : type) c = tolower(c);

				if (type == "input") {
					tmpInt2 = 0;
				}
				else if (type == "output") {
					tmpInt2 = 1;
				}
				else {
					throw std::runtime_error("INCORRECT SYNTAX!: '" + line + "'");
				}

				//get between ( and )
				//put all comma separated values in a vector 
				//signals to set as correct type

				tmpInt1++;
				line = line.substr(tmpInt1, line.find(")") - tmpInt1);
				for (auto& c : line) c = tolower(c);
				std::stringstream test(line);
				while (std::getline(test, line, ','))
				{
					trim(line);
					Signal::setSignalAsInputOrOutput(line, (bool)tmpInt2);
				}
			}
		}
		file.close();
		killGateFactory(gateFactory);
	}
	catch (const std::exception& e)
	{
		std::cerr << "Caught an error while interpreting ISCAS file!" << std::endl << e.what();
		exit(401);
	}
}

#endif INTERPRETER_C