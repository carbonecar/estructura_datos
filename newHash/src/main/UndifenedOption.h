/*
 * UndifenedOption.h
 *
 */

#ifndef UNDIFENEDOPTION_H_
#define UNDIFENEDOPTION_H_

#include "Option.h"

class UndifenedOption: public Option{
public:
	int execute(char**);
	void action();
};

#endif /* UNDIFENEDOPTION_H_ */
