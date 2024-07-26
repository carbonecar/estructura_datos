#include "Aritmetic.h"
#include "utils/utiles.h"
#include "utils/const.h"


#include <math.h>
#include <map>
#include <limits.h>
#include <list>
#include <stdlib.h>


Aritmetic::Aritmetic (istream * entrada, ostream * salida, int precision, Mode mode, bool logOn) {
	this->broadcaster = NULL;
	this->reader = NULL;
	this->mode = mode;

	if (mode == COMPRESS)
		this->broadcaster = new Broadcaster(salida);

	if (mode == UNCOMPRESS)
		this->reader = new Reader(entrada,precision);

	this->precision=precision;
	this->underflowCount = 0;

	this->aritmeticFloor = 0;
	this->aritmeticCeil = (unsigned int)pow(2,precision)-1;

	this->logOn = logOn;
	this->logger = Logger::getInstance();
}

Aritmetic::~Aritmetic() {
	if (broadcaster != NULL) delete broadcaster;
	if (reader != NULL) delete reader;
}

bool Aritmetic::isOverflow() {
	int msbFloor =  Util::getBit(aritmeticFloor,precision-1);
	int msbCeil = Util::getBit(aritmeticCeil,precision-1);

	return msbFloor == msbCeil;
}

bool Aritmetic::isUnderflow() {
	int msb2Floor = Util::getBits(aritmeticFloor,precision-1,precision-2);
	int msb2Ceil = Util::getBits(aritmeticCeil,precision-1,precision-2);

	return msb2Floor == 1 && msb2Ceil == 2;
}

void Aritmetic::resolveOverflow() {
    while(isOverflow()){

        int msb = Util::getBit(aritmeticFloor, precision - 1);
        aritmeticFloor <<= 1;
        aritmeticCeil <<= 1;

        aritmeticFloor = Util::getBits(aritmeticFloor,precision-1,0);
        aritmeticCeil = Util::getBits(aritmeticCeil,precision-1,0);

        Util::setBit(aritmeticFloor, 0, 0);
        Util::setBit(aritmeticCeil, 0, 1);


        log("Hay overflow");
        log("Piso : " + Util::bitsIntToString(aritmeticFloor,precision) + " - " + Util::uIntToString(aritmeticFloor));
        log("Techo: " + Util::bitsIntToString(aritmeticCeil,precision) + " - " + Util::uIntToString(aritmeticCeil) );

        switch(mode) {
			case COMPRESS:
				broadcaster->broadcast(msb);
				for(int i=underflowCount;i > 0;i--){
					broadcaster->broadcast(Util::getNegBit(msb));
					log("Contador de Underflow " + Util::uIntToString(underflowCount));
					log("Emision: " + Util::uIntToString(Util::getNegBit(msb)));
				}
				underflowCount = 0;
				break;

			case UNCOMPRESS:
				reader->resolveOverflow();
				break;
        }
    }
}

void Aritmetic::resolveUnderflow() {
    while(isUnderflow()) {

		aritmeticFloor <<= 1;
		aritmeticCeil <<= 1;

		aritmeticFloor = Util::getBits(aritmeticFloor,precision-1,0);
		aritmeticCeil = Util::getBits(aritmeticCeil,precision-1,0);

		Util::setBit(aritmeticFloor,precision-1,0);
		Util::setBit(aritmeticCeil,precision-1,1);
		Util::setBit(aritmeticFloor,0,0);
		Util::setBit(aritmeticCeil,0,1);

		switch(mode) {
			case COMPRESS:
				underflowCount++;
				break;
			case UNCOMPRESS:
				reader->resolveUnderflow();
				break;
		}

    	log("Hay underflow");
    	log("Piso : " + Util::bitsIntToString(aritmeticFloor,precision) + " - " + Util::uIntToString(aritmeticFloor));
    	log("Techo: " + Util::bitsIntToString(aritmeticCeil,precision) + " - " + Util::uIntToString(aritmeticCeil) );
		log("Contador de Underflow: " + Util::uIntToString(underflowCount));

	}
}

void Aritmetic::normalize() {
    resolveOverflow();
    resolveUnderflow();
}

void Aritmetic::calculateLimits(DistributionTable table,charDT charToCompress,unsigned int &newFloor, unsigned int &newCeil) {
	unsigned int cumulativeProb = table.getTotalFrequency();
	unsigned int range = (unsigned long)aritmeticCeil - aritmeticFloor + 1;

	unsigned int rescaledUpper = (unsigned long)table.getCumulativeFrequency(charToCompress) * range;
				 rescaledUpper /= (unsigned long)cumulativeProb;

	unsigned int rescaledLower = (unsigned long)table.getCummulativePreviousCharacterFrequency(charToCompress) * range;
				 rescaledLower /= (unsigned long)cumulativeProb;

	unsigned int scale = cumulativeProb / pow(2,precision-2) + 1;
	if(cumulativeProb > scale) {
		rescaledLower /=  scale;
		rescaledUpper /=  scale;
	}


	newCeil = aritmeticFloor + Util::getBits(rescaledUpper,precision-1,0) - 1;



	newFloor = aritmeticFloor +  Util::getBits(rescaledLower,precision-1,0);

	/*double pres = pow(2,precision-2);
	unsigned int range = aritmeticCeil - aritmeticFloor + 1;
	unsigned int auxFloor = aritmeticFloor;
	unsigned int scale = table.getTotalFrequency() / pres + 1;
	unsigned int lowerBound;
	unsigned int upperBound;
	unsigned int previousCharFrequency = table.getCummulativePreviousCharacterFrequency(charToCompress);
	unsigned int charFrequency = table.getCumulativeFrequency(charToCompress);

	scale = 1;

	if(previousCharFrequency == 0)
		lowerBound = 0;
	else {
		lowerBound =  previousCharFrequency / scale;
		if(lowerBound == 0) lowerBound = 1;
	}

	if(charFrequency == 0)
		upperBound = 0;
	else {
		upperBound =  charFrequency / scale;
		if(upperBound == 0) upperBound = 1;
	}

	newFloor = auxFloor + round((double)(range * lowerBound) / (table.getTotalFrequency() / scale));
	newCeil = auxFloor + floor((double)(range * upperBound) / (table.getTotalFrequency() / scale)) - 1;*/

}

void Aritmetic::compress(DistributionTable table, charDT charToCompress) {

	log("Caracter: ");
	log(charToCompress);
	log("Piso Inicial : " + Util::bitsIntToString(aritmeticFloor,precision) + " - " + Util::uIntToString(aritmeticFloor));
	log("Techo Inicial: " + Util::bitsIntToString(aritmeticCeil,precision) + " - " + Util::uIntToString(aritmeticCeil));

	calculateLimits(table,charToCompress,aritmeticFloor,aritmeticCeil);

	log("Piso Actual : " + Util::bitsIntToString(aritmeticFloor,precision) + " - " + Util::uIntToString(aritmeticFloor));
	log("Techo Actual: " + Util::bitsIntToString(aritmeticCeil,precision) + " - " + Util::uIntToString(aritmeticCeil));

	if(charToCompress != C_EOF)
		normalize();
	else
		flush();
}

charDT Aritmetic::uncompress(DistributionTable table) {
	unsigned int lowerBound;
	unsigned int upperBound;
	unsigned int readNumber = Util::getBits(reader->read(),precision-1,0);

	log("Numero leído: " + Util::bitsIntToString(readNumber,precision) + " - " + Util::uIntToString(readNumber));
	log("Piso Inicial : " + Util::bitsIntToString(aritmeticFloor,precision) + " - " + Util::uIntToString(aritmeticFloor));
	log("Techo Inicial: " + Util::bitsIntToString(aritmeticCeil,precision) + " - " + Util::uIntToString(aritmeticCeil) );

	charDT charFound = C_EOF;

	bool found = false;
	std::map<charDT,freqDT>::iterator it = table.getBegin();

	while(it != table.getEnd() && !found)	{
		calculateLimits(table,it->first, lowerBound, upperBound);

		if((lowerBound <= readNumber) && (readNumber <= upperBound)) {
			found = true;
			charFound = it->first;
		}
		it++;
	}

	aritmeticFloor =  lowerBound;
	aritmeticCeil = upperBound;

	log("Caracter leido: ");
	log(charFound);
	log("Piso Actual : " + Util::bitsIntToString(aritmeticFloor,precision) + " - " + Util::uIntToString(aritmeticFloor));
	log("Techo Actual: " + Util::bitsIntToString(aritmeticCeil,precision) + " - " + Util::uIntToString(aritmeticCeil));

	if(charFound != C_EOF)
		normalize();

	return charFound;
}

void Aritmetic::flush() {
	/* emito el primer bit del numero */
	broadcaster->broadcast(Util::getBit(aritmeticFloor,precision-1));

	/* emito el under flow si lo hay */
	unsigned int msb = Util::getBit(aritmeticFloor,precision-1);

	for(int i=underflowCount;i > 0;i--){
		broadcaster->broadcast(Util::getNegBit(msb));

		log("Contador de Underflow " + Util::uIntToString(underflowCount));
		log("Emision: " + Util::uIntToString(Util::getNegBit(msb)));
	}
	underflowCount = 0;

	/* emito los bits faltantes */
	for(unsigned int i = 0; i < precision-1;i++)
		broadcaster->broadcast(Util::getBit(aritmeticFloor,precision-2 - i));

	broadcaster->closeOutput();
}

void Aritmetic::log(charDT c) {
	std::string tmp = "";
	if(c != C_EOF)
		tmp.append(1,(char)c);
	else
		tmp.append("EOF");

	log(tmp);
}

void Aritmetic::log(std::string message) {
	if(logOn)
		logger->info(message);
}

