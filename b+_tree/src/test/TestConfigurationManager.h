/*
 * TestConfigurationManager.h
 *
 *  Created on: 01/05/2010
 *      Author: Daniel
 */

#ifndef TESTCONFIGURATIONMANAGER_H_
#define TESTCONFIGURATIONMANAGER_H_

class TestConfigurationManager {
public:
	TestConfigurationManager();
	virtual ~TestConfigurationManager();

	void runTest();

	void testInit();
};

#endif /* TESTCONFIGURATIONMANAGER_H_ */
