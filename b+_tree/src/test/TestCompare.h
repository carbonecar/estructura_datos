/*
 * TestCompare.h
 *
 *  Created on: Apr 24, 2010
 *      Author: carlos
 */

#ifndef TESTCOMPARE_H_
#define TESTCOMPARE_H_

#include "../BPlusTree/Element.h"
#include <functional>
#include <algorithm>
using namespace std;

class TestCompare {
public:
	TestCompare();
	void run();
	virtual ~TestCompare();
};

struct ElementComparator: public std::binary_function<Element,Element,bool>{
  bool operator () ( const Element& elem,const Element& elem2) const {
	return elem.getKey()==elem2.getKey();
    }
  };
#endif /* TESTCOMPARE_H_ */
