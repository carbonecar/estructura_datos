#include "PPMC_BTree.h"


/**
 * PPMC_BTree.
 *
 */

#include "../StatisticsOption.h"
#include "DataBtreeOption.h"

PPMC_BTree::PPMC_BTree(){
}

PPMC_BTree::~PPMC_BTree(){
}

Option* PPMC_BTree::createDataOption(int blockNumber,string filename){
	return new DataBtreeOption(blockNumber,filename);
}

Index* PPMC_BTree::createIndex(string filename){
	return new IndexBtree(filename);
}

Option* PPMC_BTree::DataOption(string filename){
	return new DataBtreeOption(filename);
}

Option* PPMC_BTree::statistincsOption(){
	return new StatisticsOption();
}

