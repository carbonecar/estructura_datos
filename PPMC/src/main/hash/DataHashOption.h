/*
 * DataHashOption.h
 *
 *  Created on: 26/06/2010
 *      Author: sergio
 */

#ifndef DATAHASHOPTION_H_
#define DATAHASHOPTION_H_

#include "../Option.h"
#include "../../ppmcindex/IndexHash.h"
#include "../../Persistence/exceptions/PersistExceptions.h"

class DataHashOption: public Option {
private:
	int blockNumber;
	string filename;
	IndexHash* index;

public:
	DataHashOption(int bockNumber,string filename);
	DataHashOption(string filename);
	virtual ~DataHashOption();
	int execute(char**);
	void action();

};

#endif /* DATAHASHOPTION_H_ */
