#pragma once

#include <string>
#include <cctype>
#include <algorithm>
#include <locale>
#include "../domain/Value.h"

std::string getValueName(value_t val);
int power(int base, int exponent);

// trim from start (in place)
void ltrim(std::string& s);

// trim from end (in place)
void rtrim(std::string& s);

// trim from both ends (in place)
void trim(std::string& s);

value_t getValueString(std::string str);

std::string getValueNumberAsString(value_t val);

int countCharacter(std::string toTest, char toFind);