/*
 * TestIndexBTree.cpp
 *
 *  Created on: Jun 19, 2010
 *      Author: carlos
 */

#include "TestIndexBTree.h"

TestIndexBTree::TestIndexBTree() {
	system("rm testHash*");
	ih=new IndexBtree("testHash");

}
void TestIndexBTree::runTest(){
	TestIndex::runTest();
	cout<<"segundo test"<<endl;
	charDT myChar=64;

	this->ih->addCharacter(myChar,"");
	DistributionTable* dt=this->ih->getContext("");
	cout<<"dt : "<<dt->toHuman();
	assert(dt->isCharacterInTable(myChar));

}

TestIndexBTree::~TestIndexBTree() {
}
