/*
 * DeleteOption.h
 *
 */

#ifndef DELETEOPTION_H_
#define DELETEOPTION_H_

#include "Option.h"

class DeleteOption: public Option {
public:
	DeleteOption(char** argv):Option(argv){};
	~DeleteOption(){};
	void action();
};

#endif /* DELETEOPTION_H_ */
