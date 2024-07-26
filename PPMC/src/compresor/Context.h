/*
 * Context.h
 *
 *  Created on: 09/06/2010
 *      Author: leonardo
 */

#ifndef CONTEXT_H_
#define CONTEXT_H_

#include "../ppmcindex/Index.h"
#include "../aritmetic/DistributionTable.h"
#include <string>
using namespace std;

class Context
{
protected:
	static Index * index;
	string currentContext;
	unsigned int maxOrder;

public:
	Context(unsigned int);
	virtual ~Context();

	string getStringContext();
	//Context * getPreviousContext();
	void previousContext();

	unsigned int getMaxOrder();
	void push (char);

	Context * clone();

	unsigned int getCurrentOrder();

	static void setIndex (Index *);

	void updateContext (charDT);
	void addCharacter (charDT);

	void toHuman();

	DistributionTable * getDistributionTable();
	Context & operator= (Context &);
};

#endif /* CONTEXT_H_ */
