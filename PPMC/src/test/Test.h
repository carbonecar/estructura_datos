/*
 * Test.h
 *
 *  Created on: 06/06/2010
 *      Author: daniel
 */


#include <assert.h>

#ifndef TEST_H_
#define TEST_H_

class Test {
public:
	Test();
	virtual ~Test();

	virtual void runTest() = 0;
};

#endif /* TEST_H_ */
