/*
 * TestSerialization.cpp
 *
 *  Created on: 11/04/2010
 *      Author: daniel
 */

#include "TestSerialization.h"
#include "../Persistence/Block.h"
#include "../BPlusTree/Node.h"
#include "../BPlusTree/LeafNode.h"
#include "../BPlusTree/Element.h"

TestSerialization::TestSerialization() {
}

TestSerialization::~TestSerialization() {
}

void TestSerialization::runTests() {

	try {
		testSerializeBlock();
		testSerializeElement();
		testSerializeKeyElement();
		testSerializeLeafNode();
		//testSerializeNode();
	}
	catch(std::exception e) {
		std::cout << "Test Fail:" << e.what();
	}
}



void TestSerialization::testSerializeBlock() {
	std::cout << "Test Block" << std::endl;
	std::cout << "----------" << std::endl;

	Node *nodeIni = new Node();
	Block *blockIni = nodeIni;

	nodeIni->setLevel(1);

	std::string buffer = blockIni->serialize();

	Node *nodeFin = new Node();
	Block *blockFin = nodeFin;

	nodeFin->unserialize(buffer);

	std::cout << "Level: " << nodeFin->getLevel() << std::endl;
	std::cout << "Cantidad de registros: " << nodeFin->getRegisterCounter() << std::endl;
	std::cout << std::endl;

	delete(nodeIni);
	delete(nodeFin);

}

void TestSerialization::testSerializeElement() {
	std::cout << "Test Element" << std::endl;
	std::cout << "------------" << std::endl;
	Element *elementIni = new Element();

	std::string data = "Soy serializable";

	elementIni->setData((Data)data.c_str(),data.length());
	elementIni->setKey(123);

	std::string buffer = elementIni->serialize();

	Element *elementFin = new Element();

	elementFin->unserialize(buffer);

	std::string datastr((char*)elementFin->getData(),elementFin->getElementSize());

	std::cout << "Key: " << elementFin->getKey() << std::endl;
	std::cout << "Tama�o del elemento: " << elementFin->getElementSize() << std::endl;
	std::cout << "Elemento : " << datastr << std::endl << std::endl;

	delete(elementIni);
	delete(elementFin);
}

void TestSerialization::testSerializeKeyElement() {
	std::cout << "Test Key Element" << std::endl;
	std::cout << "----------------" << std::endl;

	KeyElement *keyElementIni = new KeyElement();

	keyElementIni->setKey(245);
	keyElementIni->setRightNode(56778);

	std::string buffer = keyElementIni->serialize();

	KeyElement *keyElementFin = new KeyElement();

	keyElementFin->unserialize(buffer);

	std::cout << "Key: " << keyElementFin->getKey() << std::endl;
	std::cout << "Right Node: " << keyElementFin->getrightNode() << std::endl;
	std::cout << std::endl;

	delete keyElementIni;
	delete keyElementFin;
}

void TestSerialization::testSerializeLeafNode() {
	std::cout << "Test LeafNode" << std::endl;
	std::cout << "----------------" << std::endl;

	LeafNode *leafNodeIni = new LeafNode();

	std::string data1 = "Me guarde 1";
	std::string data2 = "Me guarde 2";
	std::string data3 = "Me guarde 3";

	leafNodeIni->insertarTest(new Element(100,(Data)data1.c_str(),data1.length()));
	leafNodeIni->insertarTest(new Element(200,(Data)data2.c_str(),data2.length()));
	leafNodeIni->insertarTest(new Element(300,(Data)data3.c_str(),data3.length()));


	std::string buffer = leafNodeIni->serialize();

	LeafNode *leafNodeFin = new LeafNode();

	leafNodeFin->unserialize(buffer);

	std::cout << "Prev Node: " << leafNodeFin->getPrevNode()<< std::endl;
	std::cout << "Next Node: " << leafNodeFin->getNextNode() << std::endl;
	std::cout << "FreeSpace: " << leafNodeFin->getFreeSpace() << std::endl;
	std::cout << std::endl;

	std::vector<Element*>::iterator it;

	for(it = leafNodeFin->getElementsBegin(); it != leafNodeFin->getElementsEnds(); it++) {
		std::cout << "Key: " << (*it)->getKey() << std::endl;
		std::cout << "Tama�o del elemento: " << (*it)->getElementSize() << std::endl;
		std::cout << "Elemento : " << (*it)->getData() << std::endl << std::endl;
	}

	std::cout << std::endl;

	delete leafNodeIni;
	delete leafNodeFin;

}

void TestSerialization::testSerializeNode() {
	std::cout << "Test Node" << std::endl;
	std::cout << "----------------" << std::endl;

	Node *nodeIni = new Node();

	nodeIni->setLeftNode(256);
	nodeIni->appendKeyElementInOrder(new KeyElement(2345,100));
	nodeIni->appendKeyElementInOrder(new KeyElement(2100,10));
	nodeIni->appendKeyElementInOrder(new KeyElement(2215,20));

	std::string buffer = nodeIni->serialize();

	Node *nodeFin = new Node();

	nodeFin->unserialize(buffer);

	std::cout << "Left Node: " << nodeFin->getLeftNode() << std::endl;
	std::cout << std::endl;

	std::vector<KeyElement*>::iterator it;

	for(it = nodeFin->getKeyElementsBegin(); it != nodeFin->getKeyElementsEnds(); it++) {
		std::cout << "Key: " << (*it)->getKey() << std::endl;
		std::cout << "Right Node: " << (*it)->getrightNode() << std::endl;
	}

	delete nodeIni;
	delete nodeFin;

	std::cout << std::endl;
}

