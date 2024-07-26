/*
 * ModifOption.h
 *
 */

#ifndef MODIFOPTION_H_
#define MODIFOPTION_H_

#include "Option.h"

class ModifOption: public Option{
public:
	ModifOption(char** argv):Option(argv){};
	~ModifOption(){};
	void action();
};

#endif /* MODIFOPTION_H_ */
