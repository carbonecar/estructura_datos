/*
 * PersistorBTree.cpp
 *
 *  Created on: 23/04/2010
 *      Author: daniel
 */

#include "PersistorBTree.h"
#include "../BPlusTree/LeafNode.h"
#include "../BPlusTree/Node.h"


PersistorBTree::PersistorBTree(std::string fileName, BlockSize size) throw() {
	/* Validaci�n de que este iniciado */
	if(fileName.length() == 0 || size == 0)
		throw new PersistorNotInitializedException();

	freeSpaceManager = new FreeSpaceManager(fileName + ".fs");

	/* Abre el archivo para lectura - escritura binario */
	this->archivo.open(fileName.c_str(), std::ios::in|std::ios::out|std::ios::binary);
	this->blockSize = size;
	this->fileName = fileName;

	if (!this->archivo.is_open()){
		this->archivo.clear();
		this->newFile(fileName);
	}

	this->archivo.seekg(0,std::ios::beg);
    /* Levanta el bloque header */
    char charBuffer[HEADER_SIZE];
    this->archivo.read(charBuffer,HEADER_SIZE);

    BlockSize test;
    memcpy(&test, &charBuffer,sizeof(BlockSize));

    if (test != size)
		throw new WrongBlockSize();
}

PersistorBTree::~PersistorBTree() {
	//delete freeSpaceManager;
	//archivo.close();
}


void PersistorBTree::newFile(std::string fileName) throw() {
	PersistorBase::newFile(fileName);

	LeafNode *root = new LeafNode();

	this->add(root);
}

BNode* PersistorBTree::getRoot() {
	std::string buffer;
	Level level;
	BNode *root;

	buffer = this->load(0);
	buffer.copy((char*)&level,sizeof(Level));

	if(level == 0)
		root = new LeafNode();
	else
		root = new Node();

	root->unserialize(buffer);
	root->setOffset(0);

	return root;
}
