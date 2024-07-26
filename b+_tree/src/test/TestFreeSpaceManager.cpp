/*
 * TestFreeSpaceManager.cpp
 *
 *  Created on: 17/04/2010
 *      Author: Daniel
 */

#include "TestFreeSpaceManager.h"
#include <iostream>

TestFreeSpaceManager::TestFreeSpaceManager() {
	fileName = "testFS.txt";
}

TestFreeSpaceManager::~TestFreeSpaceManager() {
}

void TestFreeSpaceManager::runTests() {
	try {
		testBurstPop();
		testBurstPush();
		testBurstPop();
		testRandomPush();
		testBlockUse();
	}
	catch(...) {
		std::cout << "Test Fail!";
	}
}

void TestFreeSpaceManager::testBurstPop() {
	std::cout << "Test BurstPop" << std::endl;
	std::cout << "-------------" << std::endl;
	FreeSpaceManager fsManager(fileName);

	for(int i=0; i < 1000; i++) {
		Offset offset = fsManager.pop();

		std::cout << "Offset " << i << ": " << offset << std::endl;
	}

	std::cout << "Cantidad esperada: 1000" << std::endl;
	std::cout << "Cantidad usada: " << fsManager.getUseBlockCount() << std::endl;
	std::cout << std::endl;
}

void TestFreeSpaceManager::testBurstPush() {
	std::cout << "Test BurstPush" << std::endl;
	std::cout << "--------------" << std::endl;

	FreeSpaceManager fsManager(fileName);

	std::cout << "Cantidad usada: " << fsManager.getUseBlockCount() << std::endl;

	for(int i=0; i < 1000; i++) {
		fsManager.push(i);
	}

	std::cout << "VER ARCHIVO: " << fileName << std::endl;
	std::cout << "Cantidad usada: " << fsManager.getUseBlockCount() << std::endl;
	std::cout << std::endl;
}

void TestFreeSpaceManager::testRandomPush() {
	std::cout << "Test RandomPush" << std::endl;
	std::cout << "---------------" << std::endl;
	FreeSpaceManager fsManager(fileName);

	for(int i=0; i < 1000; i+=3) {
		fsManager.push(i);
	}

	std::cout << "VER ARCHIVO: " << fileName << std::endl;
	std::cout << "Cantidad usada: " << fsManager.getUseBlockCount() << std::endl;
	std::cout << std::endl;
}

void TestFreeSpaceManager::testBlockUse() {
	std::cout << "Test BlockUse" << std::endl;
	std::cout << "---------------" << std::endl;

	FreeSpaceManager fsManager("test2.txt.fs");

	Offset offset = fsManager.pop();

	std::cout << "Bloque tomado: " << offset << std::endl;
	std::cout << "Bloque usado:" << fsManager.isBlockUsed(offset) << std::endl;

	std::cout << std::endl;
}
