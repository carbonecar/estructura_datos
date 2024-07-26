/*
 * DecompressionOption.cpp
 */

#include "DecompressionOption.h"
#include "MainPPMC.h"
#include "../compresor/PPMC.h"

DecompressionOption::DecompressionOption(MainPPMC* indexFactory) {
	this->indexFactory = indexFactory;
	this->precision = configFile->read<int>("precision");
	this->exclusion = configFile->read<bool>("exclusion");
	this->ppmcLogger = configFile->read<bool>("ppmclogger");
	this->arithmeticLogger = configFile->read<bool>("arithmeticlogger");
}

DecompressionOption::~DecompressionOption() {}

int DecompressionOption::execute(char** argv) {
	//Ejemplo de entrada: echo "DIVIDIDOS" | ./ppmc-t -d 4 -f /tmp/trabajo.pmw
	this->orden = atoi(argv[2]);
	this->filename = argv[4];
	action();
	return 0;
}

void DecompressionOption::action() {
	Index* index = this->indexFactory->createIndex(this->filename);
	PPMC* ppmc = new PPMC(this->precision, this->orden,this->ppmcLogger,this->arithmeticLogger);
	ppmc->setIndex(index);
	ppmc->unCompress(&std::cin, &std::cout, this->exclusion);
	delete ppmc;
}
