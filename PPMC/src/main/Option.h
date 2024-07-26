/*
 * Option.h
 *
 */

#ifndef OPTION_H_
#define OPTION_H_

#include "../utils/types.h"
#include "../utils/ConfigFile.h"
#include <string>
#include "../Persistence/exceptions/PersistExceptions.h"

using namespace std;
class Option {
protected:
	ConfigFile* configFile;
public:
	Option();
	virtual ~Option();
	virtual int execute(char**)=0;
	virtual void action()=0;
};

#endif /* OPTION_H_ */
