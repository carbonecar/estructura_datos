/*
 * Help.h
 *
 */

#ifndef HELPOPTION_H_
#define HELPOPTION_H_

#include "Option.h"
#include <iostream>

class HelpOption: public Option{
public:
	int execute(char**);
	void action();
};

#endif /* HELPOPTION_H_ */
