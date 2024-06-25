#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <sstream>
#include <vector>
#include <exception>


#include "../../domain/Gate/Gate.h"
#include "../../domain/Gate/AndGate.h"
#include "../../domain/Gate/NandGate.h"
#include "../../domain/Gate/NorGate.h"
#include "../../domain/Gate/NotGate.h"
#include "../../domain/Gate/OrGate.h"
#include "../../domain/Gate/XorGate.h"
#include "../../domain/Gate/XnorGate.h"
#include "../../domain/Signal.h"
#include "../../helpers/misc.h"
#include "../../helpers/gateFactory.h"

class Interpreter
{
public:
	Interpreter(std::string filename);
	~Interpreter();
	void interpret();

private:
	std::string filename;
};


#endif INTERPRETER_H