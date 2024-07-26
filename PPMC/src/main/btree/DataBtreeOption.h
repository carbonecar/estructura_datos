/*
 * DataBtreeOption.h
 *
 *  Created on: 26/06/2010
 *      Author: sergio
 */

#ifndef DATABTREEOPTION_H_
#define DATABTREEOPTION_H_

#include "../Option.h"
#include "../../ppmcindex/IndexBtree.h"
#include "../../Persistence/exceptions/PersistExceptions.h"
class DataBtreeOption: public Option {
private:
	int blockNumber;
	string filename;
	IndexBtree* index;
public:
	DataBtreeOption(int blockNumber,string filename);
	DataBtreeOption(string filename);
	virtual ~DataBtreeOption();
	int execute(char**);
	void action();
};

#endif /* DATABTREEOPTION_H_ */
