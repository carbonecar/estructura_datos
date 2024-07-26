/*
 * DataHashOption.cpp
 *
 *  Created on: 26/06/2010
 *      Author: sergio
 */

#include "DataHashOption.h"

DataHashOption::DataHashOption(int blockNumber,string filename) {
	this->blockNumber=blockNumber;
	this->filename=filename;
}
DataHashOption::DataHashOption(string filename) {
	this->blockNumber= -1;
	this->filename=filename;
}

DataHashOption::~DataHashOption() {
	delete index;
}

int DataHashOption::execute(char** argv){
	this->index=new IndexHash(this->filename);
	if( (this->blockNumber==-1)){
		this->index->toHuman();
	}else{
		try{
			this->index->toHuman(this->blockNumber);
		}catch (PersistExceptions::ElementNotFoundException* e){
			delete e;
			std::cout << "El  bloque no existe." << std::endl;
		}
	}
	return 0;
}

void DataHashOption::action(){}
