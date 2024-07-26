/*
 * CompressionOption.cpp
 */

#include "CompressionOption.h"
#include "../compresor/PPMC.h"
#include "MainPPMC.h"

CompressionOption::CompressionOption(MainPPMC* indexFactory) {
	this->indexFactory=indexFactory;
	this->precision = configFile->read<int>("precision");
	this->exclusion = configFile->read<bool>("exclusion");
	this->ppmcLogger = configFile->read<bool>("ppmclogger");
	this->arithmeticLogger = configFile->read<bool>("arithmeticlogger");
}

CompressionOption::~CompressionOption() {
	//delete indexFactory;
}


int CompressionOption::execute(char** argv){
	//Ejemplo de entrada: echo "DIVIDIDOS" | ./ppmc-t -c 4 -f /tmp/trabajo.pmw > ./archivo_comprimido.pmc
	this->orden = atoi(argv[2]);
	assert(!(this->orden>100));
	this->filename = argv[4];
	action();
	return 0;
}

void CompressionOption::action(){
	Index* index=this->indexFactory->createIndex(this->filename);
	PPMC* ppmc=new PPMC(this->precision,this->orden,this->ppmcLogger,this->arithmeticLogger);
	ppmc->setIndex(index);
	ppmc->compress(&std::cin, &std::cout, this->exclusion);
	delete index;
	delete ppmc;
}
