/*
 * TestFreeSpaceManager.h
 *
 *  Created on: 17/04/2010
 *      Author: Daniel
 */

#ifndef TESTFREESPACEMANAGER_H_
#define TESTFREESPACEMANAGER_H_

#include "../Persistence/FreeSpaceManager.h"

class TestFreeSpaceManager {
private:
	std::string fileName;

public:
	TestFreeSpaceManager();
	virtual ~TestFreeSpaceManager();

	void runTests();

	void testBurstPop();
	void testBurstPush();
	void testRandomPush();
	void testBlockUse();
};

#endif /* TESTFREESPACEMANAGER_H_ */
