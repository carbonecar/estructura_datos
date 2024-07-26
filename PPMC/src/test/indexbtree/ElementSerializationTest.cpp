/*
 * ElementSerializationTest.cpp
 *
 *  Created on: Jun 19, 2010
 *      Author: carlos
 */

#include "ElementSerializationTest.h"

#include "../../BPlusTree/Element.h"
#include <assert.h>
#include <string>

using namespace std;
ElementSerializationTest::ElementSerializationTest() {
}

ElementSerializationTest::~ElementSerializationTest() {
}

void ElementSerializationTest::run()
{

	Element* elem=new Element("10absdaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa","5aaaa",6);




	Element* serializedElement=new Element();
	string unserialize=elem->serialize();
	serializedElement->unserialize(unserialize);

	assert( (elem->getKey()==serializedElement->getKey()));
	cout<<serializedElement->getData()<<endl;
	assert( !(strcmp(elem->getData(),serializedElement->getData())));

	cout<<elem->getData()<<endl;

	delete serializedElement;
	delete elem;
}


