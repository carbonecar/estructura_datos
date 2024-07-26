/*
 * TestSerialization.h
 *
 *  Created on: 11/04/2010
 *      Author: daniel
 */

#ifndef TESTSERIALIZATION_H_
#define TESTSERIALIZATION_H_

#include <iostream>

class TestSerialization {
private:


public:
	TestSerialization();
	virtual ~TestSerialization();

	void runTests();

	void testSerializeBlock();
	void testSerializeElement();
	void testSerializeKeyElement();
	void testSerializeLeafNode();
	void testSerializeNode();


};

#endif /* TESTSERIALIZATION_H_ */
