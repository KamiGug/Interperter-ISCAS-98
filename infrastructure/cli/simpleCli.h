#ifndef SIMPLECLI_H
#define SIMPLECLI_H

//#define DEBUG

#include <string>
#include <vector>
#include <map>
#include <functional>

#include "../Outputer/Outputer.h"
#include "../Outputer/SimpleOutputer.h"
#include "../Outputer/TextRaportOutputer.h"
#include "../Outputer/CsvInputOutputer.h"
#include "../Tester/Tester.h"
#include "../Tester/BinaryNumberTester.h"
#include "../Tester/CsvTester.h"


void parseArgs(int argc, char* argv[], Tester*& tester, Outputer*& outputer, std::string& iscas, std::string& ftl);



#endif