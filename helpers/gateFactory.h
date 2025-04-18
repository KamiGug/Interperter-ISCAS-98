#pragma once

#include <map>
#include <functional>

#include "../domain/Gate/Gate.h"
#include "../domain/Gate/AndGate.h"
#include "../domain/Gate/NandGate.h"
#include "../domain/Gate/NorGate.h"
#include "../domain/Gate/NotGate.h"
#include "../domain/Gate/OrGate.h"
#include "../domain/Gate/XorGate.h"
#include "../domain/Gate/XnorGate.h"
#include "../domain/Signal.h"
#include "../domain/Gate/FlipFlop/FlipFlop.h"
#include "../domain/Gate/FlipFlop/DFlipFlop.h"


typedef std::map<std::string, std::function<Gate *(std::vector<std::string> inputs, std::string output, std::string clk)>> gateFactory_t;

gateFactory_t* initGateFactory(); 

void killGateFactory(gateFactory_t* toKill);