/*
 * TestIndexBTree.h
 *
 *  Created on: Jun 19, 2010
 *      Author: carlos
 */

#ifndef TESTINDEXBTREE_H_
#define TESTINDEXBTREE_H_

#include "TestIndex.h"
#include "../../ppmcindex/IndexBtree.h"

class TestIndexBTree: public TestIndex {
public:
	TestIndexBTree();
	void runTest();
	virtual ~TestIndexBTree();
};

#endif /* TESTINDEXBTREE_H_ */
