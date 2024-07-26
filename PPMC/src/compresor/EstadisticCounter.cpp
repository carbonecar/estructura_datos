/*
 * EstadisticCounter.cpp
 *
 *  Created on: Jun 26, 2010
 *      Author: carlos
 */

#include "EstadisticCounter.h"
#include <stdio.h>
#include <iostream>
EstadisticCounter::EstadisticCounter() {}

void EstadisticCounter::addContextHit(string context)
{
	map<string, unsigned int>::iterator itContextHist=this->contextHits.find(context);
	if(itContextHist==this->contextHits.end()){
		//esta vacio asi que le agrego el contexto con un valor de 1 :D
		this->contextHits.insert(pair<string,unsigned int>(context,1));
	}else{
		//le sumo uno al valor
		itContextHist->second++;
	}
}

EstadisticCounter::~EstadisticCounter() {
	//escribimos a archivo las estadisticas
	std::fstream archivo;

	archivo.open("statics.txt", std::ios::out | std::ios::binary);

	archivo<<*this;

	archivo.close();


}
ostream& operator<<(ostream& myOstream,  EstadisticCounter& elem){

	myOstream<<"Tamaño inicial del archivo: "<<elem.originalFilesize<<endl;
	myOstream<<"Tamaño final del archivo: "<<elem.finalFilesize<<endl;

	myOstream<<"Hits por contexto"<<endl;
	map<string,unsigned int>::iterator itContextxHits=elem.contextHits.begin();

	while(itContextxHits!=elem.contextHits.end()){
		myOstream<<"Contexto: <"<<itContextxHits->first<<"> ";
		myOstream<<"Aciertos: "<<itContextxHits->second<<endl;

		itContextxHits++;
	}

	return myOstream;
}


