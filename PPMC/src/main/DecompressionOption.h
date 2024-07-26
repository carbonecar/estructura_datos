/*
 * DecompressionOption.h
 */

#ifndef DECOMPRESSIOPTION_H_
#define DECOMPRESSIOPTION_H_

#include "../ppmcindex/Index.h"
#include "Option.h"

class MainPPMC;

class DecompressionOption: public Option {
private:
	 MainPPMC* indexFactory;
	 string filename;
	 int precision;
	 int orden;
	 bool exclusion;
	 bool ppmcLogger;
	 bool arithmeticLogger;

public:
	DecompressionOption(MainPPMC* indexFactory);
	virtual ~DecompressionOption();
	int execute(char**);
	void action();
};

#endif /* DECOMPRESSIONPTION_H_ */
