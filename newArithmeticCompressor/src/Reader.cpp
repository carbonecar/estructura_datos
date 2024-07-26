/*
 * Reader.cpp
 *
 *  Created on: 20/06/2010
 *      Author: Daniel
 */

#include "Reader.h"
#include "utils/utiles.h"

#include <math.h>
#include <string.h>


Reader::Reader(std::istream * input,unsigned int precision) {
	this->input = input;
	this->precision = precision;

	this->bitCounter = 0;
	this->bytesCounter = 0;
	this->maxCounter = 0;

	this->readBuffer = 0;

	/* cargo el buffer con la cantidad de bytes correspondientes a la presicion */
	unsigned int bytes = (unsigned int) ceil((double)precision / 8);
	unsigned int resto = precision % 8;

	char * tmpBufferChar = new char[bytes];
	char swap;

	this->input->seekg(0, std::ios::beg);
	this->input->read(tmpBufferChar,bytes);
	//this->input->read((char*)&readBuffer,bytes);

	for(unsigned int i = 0; i < bytes - i; i++) {
		swap = tmpBufferChar[i];
		tmpBufferChar[i] = tmpBufferChar[bytes - i - 1];
		tmpBufferChar[bytes - i - 1] = swap;
	}

	memcpy(&readBuffer,tmpBufferChar,bytes);

	delete tmpBufferChar;

	if(resto != 0) {
		tmpBuffer = (unsigned char)Util::getBits(readBuffer,8 - resto,0);
		tmpBuffer <<= resto;
		bitCounter = resto;
		readBuffer >>= 8 - resto;
	}
}

Reader::~Reader() {
	this->input = NULL;
}

void Reader::resolveOverflow() {
	readTmpBuffer();

	readBuffer <<= 1; //Shiftea
	readBuffer = Util::getBits(readBuffer,precision-1,0); //Recorta

	Util::setBit(readBuffer,0,getMSBTmpBuffer());
}

void Reader::resolveUnderflow() {
	readTmpBuffer();

	unsigned short int msb = Util::getBit(readBuffer,precision-1);
	readBuffer <<= 1; //Shiftea

	Util::setBit(readBuffer,precision-1,msb);
	readBuffer = Util::getBits(readBuffer,precision-1,0); //Recorta

	Util::setBit(readBuffer,0,getMSBTmpBuffer());
}

unsigned int Reader::read() {
	return readBuffer;
}


void Reader::readTmpBuffer() {
	if((bitCounter) % 8 == 0)
		*(this->input) >> this->tmpBuffer;
}

unsigned short int Reader::getMSBTmpBuffer() {
	/* como el buffer temporal es 1byte, leo el byte mas significativo */
	unsigned short int msb;
	msb = Util::getBit(tmpBuffer,7);
	tmpBuffer <<= 1;
	bitCounter++;

	return msb;

}

