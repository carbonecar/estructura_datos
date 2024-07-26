#ifndef Arimetic_h
#define Arimetic_h

#include <string>
#include <map>
#include <iostream>

#include "DistributionTable.h"
#include "Broadcaster.h"
#include "Reader.h"
#include "logger/Logger.h"

using namespace std;


class Aritmetic {
public:
    /* Define el modo: Compresion o descompresion */
    enum Mode{COMPRESS, UNCOMPRESS};


    Aritmetic (istream * entrada, ostream * salida, int precision, Mode str,bool logOn);
    virtual ~Aritmetic();

    /* Comprime un caracter segun la tabla de probabilidades indicada */
    void compress(DistributionTable table, charDT charToCompress);

    /* Descomprime un caracter tomando como entrada el stream pasado en el constructor
     * y utlizando la tabla de distribucion indicada */
    charDT uncompress(DistributionTable table);

 //private:

    bool isOverflow();
    bool isUnderflow();


private:
	unsigned int aritmeticFloor;
	unsigned int aritmeticCeil;

	unsigned int underflowCount;
	unsigned int precision;

	Broadcaster * broadcaster;
	Reader * reader;

	Logger* logger;

	Mode mode;
	bool logOn;

	void resolveUnderflow();
	void resolveOverflow();
    void normalize();
    void calculateLimits(DistributionTable table,charDT charToCompress,unsigned int &newFloor, unsigned int &newCeil);
    void flush();
    void log(charDT c);
    void log(std::string message);
};

#endif // Arimetic_h
