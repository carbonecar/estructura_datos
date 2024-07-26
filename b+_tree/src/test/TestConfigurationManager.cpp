/*
 * TestConfigurationManager.cpp
 *
 *  Created on: 01/05/2010
 *      Author: Daniel
 */

#include "TestConfigurationManager.h"
#include "../utils/ConfigurationMananger.h"
#include <iostream>

TestConfigurationManager::TestConfigurationManager() {
}

TestConfigurationManager::~TestConfigurationManager() {
}

void TestConfigurationManager::runTest() {
	try {
		testInit();
	} catch (...) {
		std::cout << "Test Fail!";
	}
}

void TestConfigurationManager::testInit() {
	ConfigurationMananger *cm = ConfigurationMananger::getInstance();

	std::cout << "BlockSize: " << cm->getBufferSize() << std::endl;
	std::cout << "BlocSizeTree: " << cm->getBufferSizeTree() << std::endl;
	std::cout << "Porcentaje Carga: " << cm->getChargeFactor() << std::endl;
	std::cout << "Tamaño minimo de registro: " << cm->getMinRecordSizeTree() << std::endl;
	std::cout << "Tamaño maximo de registro: " << cm->getMaxRecordSizeTree() << std::endl;
}
