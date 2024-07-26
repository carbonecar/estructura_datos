/*
 * TestIndexHash.h
 *
 *  Created on: 14/06/2010
 *      Author: ssoria
 */

#ifndef TESTINDEX_H_
#define TESTINDEX_H_

#include "../Test.h"
#include "../../ppmcindex/Index.h"
#include "../../exceptions/PPMCExceptions.h"
#include "../../utils/types.h"
#include <string>
#include <iostream>
#include <cstdio>
using namespace std;
class TestIndex: public Test {
protected:
	Index* ih;
public:
	TestIndex();
	virtual ~TestIndex();

	void runTest();
	void test1(std::string context, charDT newChar,bool insert);
};

#endif /* TESTINDEXHASH_H_ */
