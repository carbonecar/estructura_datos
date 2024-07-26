/*
 * Persistor.cpp
 *
 *  Created on: Apr 3, 2010
 *      Author: sergio
 */

#include "Persistor.h"

/* Atributos estaticos */
std::string 	Persistor::fileName = "";
BlockSize		Persistor::blockSize = 0;
PersistorBTree*  Persistor::instance = NULL;

PersistorBTree* Persistor::getInstance() throw() {
	if(Persistor::instance == NULL)
		Persistor::instance = new PersistorBTree(Persistor::fileName, Persistor::blockSize);

	return Persistor::instance;
}

PersistorBTree* Persistor::createInstance(std::string fileName,BlockSize size) {
	return new PersistorBTree(fileName,size);
}

void Persistor::init(std::string fileName,BlockSize size) throw() {

	if(Persistor::instance != NULL) {
		throw new PersistorInitializedException();
	}

	Persistor::fileName = fileName;
	Persistor::blockSize = size;
}

