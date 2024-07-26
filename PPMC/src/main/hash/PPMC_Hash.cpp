#include "PPMC_Hash.h"


/**
 * PPMC_Hash.
 *
 */

#include "../StatisticsOption.h"
#include "DataHashOption.h"

PPMC_Hash::PPMC_Hash(){}

PPMC_Hash::~PPMC_Hash(){}

Option* PPMC_Hash::createDataOption(int blockNumber,string filename){
	return new DataHashOption(blockNumber,filename);
}
Index* PPMC_Hash::createIndex(string filename){
	return new IndexHash(filename);
}

Option* PPMC_Hash::DataOption(string filename){
	return new DataHashOption(filename);
}

Option* PPMC_Hash::statistincsOption(){
	return new StatisticsOption();
}
