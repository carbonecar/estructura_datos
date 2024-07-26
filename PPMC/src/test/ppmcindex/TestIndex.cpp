/*
 * TestIndexHash.cpp
 *
 *  Created on: 14/06/2010
 *      Author: ssoria
 */

#include "TestIndex.h"
#include "../../logger/Logger.h"

#include <string>
#include <iostream>

TestIndex::TestIndex(){

}

TestIndex::~TestIndex() {
	delete ih;
}

void TestIndex::runTest(){
	for (int i = 0 ; i < 257 ; i++){
		if (i == 15){
			std::cout << std::endl;
		}
		test1("",(charDT)i,true);
		test1("a",(charDT)i,true);
		test1("ab",(charDT)i,true);
		test1("ad",(charDT)i,true);
		test1("ac",(charDT)i,true);
		test1("abc",(charDT)i,true);
		test1("adc",(charDT)i,true);
		test1("acc",(charDT)i,true);
	}
	this->ih->toHuman();
}

void TestIndex::test1(std::string context, charDT newChar,bool insert){

	try{
		if (insert)
			ih->addCharacter(newChar,context);
		DistributionTable* dt = ih->getContext(context);
		std::cout << "Existe contexto '" << context << "'" << std::endl;
		if (dt->isCharacterInTable(newChar))
			std::cout << "existe '"<< (charDT)newChar <<"' contexto '" << context << "'" << std::endl;
		else
			std::cout << "No existe '"<< (charDT)newChar <<"' contexto '" << context << "'" << std::endl;
		delete(dt);
	}catch(PPMCExceptions::ContextNotFoundException* e){
		delete(e);
		std::cout << "No existe contexto '" << context << "'" << std::endl;
	}
}


