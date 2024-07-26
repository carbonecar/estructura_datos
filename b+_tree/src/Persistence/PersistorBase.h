/*
 * PersistorBase.h
 *
 *  Created on: 16/04/2010
 *      Author: sergio
 */

#ifndef PERSISTORBASE_H_
#define PERSISTORBASE_H_

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include "../utils/types.h"
#include "Block.h"
#include "FreeSpaceManager.h"
#include "exceptions/FileNotFoundexception.h"
#include "exceptions/FailFileWriteException.h"
#include "exceptions/NotFindFreeNodeException.h"
#include "exceptions/PersistorInitializedException.h"
#include "exceptions/PersistorNotInitializedException.h"
#include "exceptions/WrongBlockSize.h"

#define HEADER_SIZE 512

class PersistorBase {
protected:
	std::fstream  archivo;
	BlockSize	blockSize;
	FreeSpaceManager*	freeSpaceManager;
	std::string fileName;

	virtual void newFile(std::string fileName) throw();
	unsigned int size();

public:
	PersistorBase();
	PersistorBase(std::string fileName, BlockSize size) throw();
	virtual ~PersistorBase();

	void modify(Block* block) throw();
	void load(Offset key, Block* block) throw();
	std::string load(Offset key) throw();
	void add(Block* block);
	void removeBlock(Offset offset);
	void deleteFile();
	void empty() throw();
	unsigned int blocks();

};

#endif /* PERSISTORBASE_H_ */
