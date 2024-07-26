/*
 * TestPersistor.h
 *
 *  Created on: 16/04/2010
 *      Author: daniel
 */

#ifndef TESTPERSISTOR_H_
#define TESTPERSISTOR_H_

#include <string>
#include "../utils/types.h"

class TestPersistor {
private:
	std::string fileName;
	BlockSize blockSize;

public:
	TestPersistor();
	virtual ~TestPersistor();

	void runTests();

	void testInit();
	void testAddNode();
	void testAddLeafNode();
	void testLoadNode();
	void testLoadLeafNode();
	void testModifyLeafNode();
	void testRemoveLeafNode();
	void testRootNode();
};

#endif /* TESTPERSISTOR_H_ */
