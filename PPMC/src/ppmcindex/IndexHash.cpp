#include "IndexHash.h"
#include "../utils/const.h"
#include "../utils/ConfigFile.h"
#include <sstream>

IndexHash::IndexHash(string file):Index(){
	ConfigFile* cf = new ConfigFile("config.txt","=","#","EndConfigFile");
	directory = new Directory(file.append("_hash"),cf->read<unsigned int>("hashBlockSize"));
	try {
		Index::getContext("");
	} catch (PPMCExceptions::ContextNotFoundException* e) {
		DistributionTable* dtTmp = new DistributionTable();
		directory->insert("" ,dtTmp->serialize());
		delete e;
		delete dtTmp;
	}
	delete(cf);
}


IndexHash::~IndexHash(){
	delete(directory);
}

void IndexHash::insertIndexStructure(string context,DistributionTable* dt){
	directory->insert(context ,dt->serialize());
}

string IndexHash::findInIndexStructre(string context){
	return directory->find(context);
}

void IndexHash::modifyInIndexStructure(string prevContext, DistributionTable* dtTmp){
	directory->modify(prevContext,dtTmp->serialize());
}

void IndexHash::structureToHuman(){
	directory->inform();
}

void IndexHash::structureToHuman(int blockNumber){
	directory->inform((Offset)blockNumber);
}





