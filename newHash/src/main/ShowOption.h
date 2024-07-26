/*
 * ShowOption.h
 *
 */

#ifndef SHOWOPTION_H_
#define SHOWOPTION_H_

#include "Option.h"

class ShowOption: public Option{
public:
	ShowOption(char** argv):Option(argv){};
	~ShowOption(){};
	int execute(char**);
	void action();
};

#endif /* SHOWOPTION_H_ */
