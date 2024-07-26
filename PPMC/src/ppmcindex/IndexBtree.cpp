#include "IndexBtree.h"



IndexBtree::IndexBtree(string filename){

	ConfigurationMananger* c = ConfigurationMananger::getInstance();

	this->bplusTree=new BPlusTree(c->getBufferSizeTree(),filename.append("btree.txt"));

	try{
		Index::getContext("");
	}catch(PPMCExceptions::ContextNotFoundException* e){
		DistributionTable* dtTmp = new DistributionTable();
		this->bplusTree->insert(new Element("",dtTmp));
		delete e;
	}
}

void IndexBtree::insertIndexStructure(string context,DistributionTable* dt){

	this->bplusTree->insert(new Element(context,dt));
}

string IndexBtree::findInIndexStructre(string context){
	Element* element=this->bplusTree->findExact(context);
	string dataString;
	dataString.append(element->getData(),element->getDataSize());
	return dataString;
}

void IndexBtree::modifyInIndexStructure(string prevContext, DistributionTable* dt){

	this->bplusTree->modify(new Element(prevContext,dt));
}


IndexBtree::~IndexBtree(){
	delete this->bplusTree;
}

void IndexBtree::structureToHuman(){
	this->bplusTree->exportTree();
}

void IndexBtree::structureToHuman(int blockNumber)
{

	this->bplusTree->exportTree(blockNumber);
}






