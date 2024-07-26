/*
 * DataBtreeOption.cpp
 *
 *  Created on: 26/06/2010
 *      Author: sergio
 */

#include "DataBtreeOption.h"

/**
 * Mostramos el arbol completo o  el nodo que se haya pasado
 */
DataBtreeOption::DataBtreeOption(int blockNumber,string filename) {
	this->blockNumber=blockNumber;
	this->filename=filename;
}

DataBtreeOption::DataBtreeOption(string filename){
	this->filename=filename;
	this->blockNumber=-1;
}
DataBtreeOption::~DataBtreeOption() {
	delete index;
}


int DataBtreeOption::execute(char** argv){
	this->index=new IndexBtree(this->filename);
	if( (this->blockNumber==-1)){
		this->index->toHuman();
	}else{
		try{
			this->index->toHuman(this->blockNumber);
		}catch(PersistExceptions::ElementNotFoundException* ex){
			cout<<"No existe el bloque solicitado: "<<this->blockNumber<<endl;
			delete ex;
		}
	}
	return 0;
}

void DataBtreeOption::action(){


}
