/*
 * EstadisticCounter.h
 *
 *  Created on: Jun 26, 2010
 *      Author: carlos
 */

#ifndef ESTADISTICCOUNTER_H_
#define ESTADISTICCOUNTER_H_

#include <map>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class EstadisticCounter {
private:
	unsigned long originalFilesize;
	unsigned long finalFilesize;
	map<string,unsigned int> contextHits;

public:

	void addContextHit(string context);

	EstadisticCounter();
	virtual ~EstadisticCounter();


	unsigned long getFinalFilesize() const
    {
        return finalFilesize;
    }

    void setFinalFilesize(unsigned long  finalFilesize)
    {
        this->finalFilesize = finalFilesize;
    }


    void printStatics();
    unsigned long getOriginalFilesize() const
    {
        return originalFilesize;
    }

    void setOriginalFilesize(unsigned long  originalFilesize)
    {
        this->originalFilesize = originalFilesize;
    }

    friend ostream& operator<<(ostream&, EstadisticCounter&);

};

#endif /* ESTADISTICCOUNTER_H_ */
