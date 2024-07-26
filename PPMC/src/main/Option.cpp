/*
 * Option.cpp
 *
 */

#include "Option.h"

const char* FileName = "config.txt";

Option::Option() {
	configFile = new ConfigFile(FileName);
}

Option::~Option() {
	delete configFile;
}
