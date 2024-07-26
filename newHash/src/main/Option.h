/*
 * Option.h
 *
 */

#ifndef OPTION_H_
#define OPTION_H_

#include "../Hash/Directory.h"
#include "../utils/types.h"
#include "../utils/ConfigFile.h"
#include <string>

class Option {
protected:
	Key key;
	std::string value;
	Directory* dir;
	ConfigFile* configFile;
	void parser(std::string line);
public:
	Option();
	Option(char**);
	virtual ~Option();
	virtual int execute(char**);
	virtual void action()=0;
};

#endif /* OPTION_H_ */
