/*
 * TestIndexHash.h
 *
 *  Created on: Jun 19, 2010
 *      Author: carlos
 */

#ifndef TESTINDEXHASH_H_
#define TESTINDEXHASH_H_
#include "../../ppmcindex/IndexHash.h"
#include "TestIndex.h"
#include "../../exceptions/PPMCExceptions.h"
#include <string>

class TestIndexHash: public TestIndex {

public:
	TestIndexHash();
	virtual ~TestIndexHash();
};

#endif /* TESTINDEXHASH_H_ */
