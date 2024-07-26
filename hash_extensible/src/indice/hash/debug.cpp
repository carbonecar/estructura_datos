/*
 * debug.cpp
 *
 *  Created on: 24/10/2009
 *      Author: leonardo
 */

#include "debug.h"

Debug::Debug()
{
}

Debug::~Debug()
{
}

void Debug::write(string data)
{
	cout << data;
}

void Debug::writeln(string data)
{
	data.append("\n");
	this->write(data);
}
