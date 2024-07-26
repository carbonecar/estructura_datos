/*
 * TestCompresor.h
 *
 *  Created on: 19/06/2010
 *      Author: leonardo
 */

#ifndef TESTCOMPRESOR_H_
#define TESTCOMPRESOR_H_

#include "../Test.h"

class TestCompresor: public Test {
public:
	TestCompresor();
	virtual ~TestCompresor();

	void runTest();

	void testCompressExclusive();
	void testUncompressExclusive();
	void testCompressNonExclusive();
	void testUncompressNonExclusive();
};

#endif /* TESTCOMPRESOR_H_ */
