/*
 * TestPersistor.cpp
 *
 *  Created on: 16/04/2010
 *      Author: daniel
 */

#include "TestPersistor.h"

#include <list>
#include "../Persistence/Persistor.h"
#include "../Persistence/Block.h"
#include "../BPlusTree/Element.h"
#include "../BPlusTree/LeafNode.h"
#include "../BPlusTree/Node.h"

TestPersistor::TestPersistor() {
	fileName = "testPersistor";
	blockSize = 1024;
}

TestPersistor::~TestPersistor() {
}

void TestPersistor::runTests() {

	try {
		testInit();
		testAddLeafNode();
		testLoadLeafNode();
		testModifyLeafNode();
		testLoadLeafNode();
		testRemoveLeafNode();
		testRootNode();
	}
	catch(...) {
		std::cout << "Test Fail!";
	}
}

void TestPersistor::testInit() {
	std::cout << "Test Persistor Initialization" << std::endl;
	try {
		//Persistor::init("test.txt",1024);
		//PersistorBTree *persistor = Persistor::getInstance();
		PersistorBTree *persistor = Persistor::createInstance(fileName,blockSize);
		persistor->deleteFile();
		delete persistor;
	}
	/*catch(PersistorNotInitializedException e) {
		std::cout << "Pas� Test!" << std::endl;
	}*/
	catch(...) {
		std::cout << "Error en test!" << std::endl;
	}

	//std::cout << "Error en test!" << std::endl;


	std::cout << std::endl;

}

void TestPersistor::testAddLeafNode() {
	std::cout << "Test Persistor Add LeafNode" << std::endl;
	LeafNode *leafNodo = new LeafNode();

	std::string data1 = "Me guarde 1";
	std::string data2 = "Me guarde 2";
	std::string data3 = "Me guarde 3";

	leafNodo->setLevel(0);
	leafNodo->setOffset(0);
	leafNodo->insertarTest(new Element(100,(Data)data1.c_str(),data1.length()));
	leafNodo->insertarTest(new Element(200,(Data)data2.c_str(),data2.length()));
	leafNodo->insertarTest(new Element(300,(Data)data3.c_str(),data3.length()));

	//PersistorBTree *persistor = Persistor::getInstance(); //REFACTOR
	PersistorBTree *persistor = Persistor::createInstance(fileName,blockSize);

	persistor->add(leafNodo);

	delete persistor;
	delete leafNodo;
}

void TestPersistor::testLoadLeafNode() {
	LeafNode *leafNodo = new LeafNode();

	//PersistorBTree *persistor = Persistor::getInstance(); //REFACTOR
	PersistorBTree *persistor = Persistor::createInstance(fileName,blockSize);

	persistor->load(1,leafNodo);

	std::cout << "Prev Node: " << leafNodo->getPrevNode()<< std::endl;
	std::cout << "Next Node: " << leafNodo->getNextNode() << std::endl;
	std::cout << "FreeSpace: " << leafNodo->getFreeSpace() << std::endl;
	std::cout << std::endl;

	std::vector<Element*>::iterator it;

	for(it = leafNodo->getElementsBegin(); it != leafNodo->getElementsEnds(); it++) {
		std::cout << "Key: " << (*it)->getKey() << std::endl;
		std::cout << "Tama�o del elemento: " << (*it)->getElementSize() << std::endl;
		std::cout << "Elemento : " << (*it)->getData() << std::endl << std::endl;
	}

	std::cout << std::endl;

	delete persistor;
	delete leafNodo;
}

void TestPersistor::testModifyLeafNode() {
	LeafNode *leafNodo = new LeafNode();

	//PersistorBTree *persistor = Persistor::getInstance(); REFACTOR
	PersistorBTree *persistor = Persistor::createInstance(fileName,blockSize);
	persistor->load(1,leafNodo);

	Element* el = leafNodo->getElement(200);

	std::string data = "Me modifique!!";

	el->setData((Data)data.c_str(),data.length());

	persistor->modify(leafNodo);


	delete leafNodo;

}


void TestPersistor::testAddNode() {
}


void TestPersistor::testLoadNode() {
}

void TestPersistor::testRemoveLeafNode(){
	//PersistorBTree *persistor = Persistor::getInstance(); REFACTOR
	PersistorBTree *persistor = Persistor::createInstance(fileName,blockSize);
	persistor->removeBlock(0);

	delete persistor;
}

void TestPersistor::testRootNode() {
	PersistorBTree *bPersistor = new PersistorBTree("testNode.txt",512);

	BNode *root = bPersistor->getRoot();

	std::cout << "Level: " << root->getLevel() << std::endl;

	delete bPersistor;
	delete root;
}
