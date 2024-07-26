/*
 * TestIndexHash.cpp
 *
 *  Created on: 14/06/2010
 *      Author: ssoria
 */

#include "TestIndexHash.h"
#include "../../logger/Logger.h"

#include <string>
#include <iostream>

TestIndexHash::TestIndexHash():TestIndex() {
	ih= new IndexHash("testHash");
}

TestIndexHash::~TestIndexHash() {}


