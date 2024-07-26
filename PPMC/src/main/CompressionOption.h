/*
 * CompressionOption.h
 */

#ifndef COMPRESSIONOPTION_H_
#define COMPRESSIONOPTION_H_

#include "Option.h"
#include "../ppmcindex/Index.h"
#include <stdlib.h>
class MainPPMC;

class CompressionOption: public Option {
private:
	MainPPMC* indexFactory;
	string filename;
	int precision;
	int orden;
	bool exclusion;
	bool ppmcLogger;
	bool arithmeticLogger;

public:
	CompressionOption(MainPPMC* indexFactory);
	virtual ~CompressionOption();
	int execute(char**);
	void action();
};

#endif /* COMPRESSIONOPTION_H_ */
