/*
 * Reader.h
 *
 *  Created on: 20/06/2010
 *      Author: Daniel
 */

#ifndef READER_H_
#define READER_H_

#include <iostream>

class Reader {
private:
	std::istream * input;
	unsigned int precision;
	unsigned int readBuffer;
	unsigned char tmpBuffer;

	unsigned int bitCounter;
	unsigned int bytesCounter;
	unsigned int maxCounter;

	void readTmpBuffer();
	unsigned short int getMSBTmpBuffer();

public:
	Reader(std::istream * input,unsigned int precision);
	virtual ~Reader();

	void resolveOverflow();
	void resolveUnderflow();

	unsigned int read();
};

#endif /* READER_H_ */
