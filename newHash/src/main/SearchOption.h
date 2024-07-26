/*
 * SearchOption.h
 *
 */

#ifndef SEARCHOPTION_H_
#define SEARCHOPTION_H_

#include "Option.h"

class SearchOption: public Option{
public:
	SearchOption(char** argv):Option(argv){};
	~SearchOption(){};
	void action();
};

#endif /* SEARCHOPTION_H_ */
