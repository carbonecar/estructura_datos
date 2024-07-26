#include "Index.h"

Index::Index(){

}

DistributionTable* Index::getContext(string context) {
	DistributionTable* dtTmp = NULL;
	try {
		dtTmp = new DistributionTable();
		dtTmp->unserialize(this->findInIndexStructre(context));
	} catch (exception* e) {
		delete (e);
		throw new PPMCExceptions::ContextNotFoundException();
	}

	return dtTmp;
}

void Index::updateContext(charDT character, string prevContext) {
	DistributionTable* dtTmp = getContext(prevContext);
	dtTmp->updateFrequency(character);
	this->modifyInIndexStructure(prevContext, dtTmp);
}

void Index::addCharacter(charDT character, string context) {
	try {
		DistributionTable* dtTmp = getContext(context);
		dtTmp->addCharacter(character);
		this->modifyInIndexStructure(context, dtTmp);
	} catch (PPMCExceptions::ContextNotFoundException* e) {
		DistributionTable* dtTmp = new DistributionTable();
		dtTmp->addCharacter(character);
		this->insertIndexStructure(context, dtTmp);
		delete e;
	}
}

bool Index::contextExists(string context) {
	try {
		this->findInIndexStructre(context);
	} catch (exception* e) {
		delete e;
		return false;
	}
	return true;
}

void Index::toHuman(){
	this->structureToHuman();
}

void Index::toHuman(int blockNumber)
{
	this->structureToHuman(blockNumber);
}





