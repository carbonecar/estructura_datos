/*
 * TestAritmetic.h
 *
 *  Created on: 06/06/2010
 *      Author: daniel
 */

#ifndef TESTARITMETIC_H_
#define TESTARITMETIC_H_

#include "../Test.h"
#include "../../aritmetic/Arithmetic.h"

class TestAritmetic: public Test {
public:
	TestAritmetic();
	virtual ~TestAritmetic();

	void runTest();

	void testCompression(unsigned int precision);
	void testUncompression(unsigned int precision);
	void testCompression2(unsigned int precision);
	void testUncompression2(unsigned int precision);
	void testCompressTexto();
	void testBitFunctions();
};

#endif /* TESTARITMETIC_H_ */
