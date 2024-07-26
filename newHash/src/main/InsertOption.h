/*
 * InsertOption.h
 *
 */

#ifndef INSERTOPTION_H_
#define INSERTOPTION_H_

#include "Option.h"

class InsertOption: public Option {
public:
	InsertOption(char** argv):Option(argv){};
	~InsertOption(){};
	void action();
};

#endif /* OPTIONINSERT_H_ */
