/*
 * AllTest.cpp
 *
 *  Created on: Jun 19, 2010
 *      Author: carlos
 */

#include "AllTest.h"
#include "ElementSerializationTest.h"
AllTest::AllTest() {}

void AllTest::run()
{

	ElementSerializationTest elementSerializationTest;
	elementSerializationTest.run();
}

AllTest::~AllTest() {
	// TODO Auto-generated destructor stub
}
