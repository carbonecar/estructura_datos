/*
 * Broadcaster.cpp
 *
 *  Created on: 20/06/2010
 *      Author: daniel
 */

#include "Broadcaster.h"
#include "utils/utiles.h"
#include "utils/const.h"

Broadcaster::Broadcaster(std::ostream * output) {
	this->broadcastBuffer = 0;
	this->counter = 0;
	this->output = output;

}

Broadcaster::~Broadcaster() {
}


void Broadcaster::broadcast(short int bit) {
	this->addBit(bit);

	if(isBroadcastFull())
		saveBroadcast();
	else
		broadcastBuffer = broadcastBuffer << 1;
}

void Broadcaster::broadcast(std::string bits) {
	//isBroadcastFull();
	//broadcastString.append(bits);
}

void Broadcaster::closeOutput() {
	/* completo con un uno y todos ceros */
	this->addBit(1);

	while(!isBroadcastFull()) {
		broadcastBuffer = broadcastBuffer << 1;
		this->addBit(0);
	}
	saveBroadcast();
}

void Broadcaster::saveBroadcast() {
	/* envia los bits almacenados en broadcasInt a la salida */
	*output << broadcastBuffer;

	/* resetea el contador y el broadcast*/
	counter = 0;
	broadcastBuffer = 0;
}

bool Broadcaster::isBroadcastFull() {
	/* si se almacena un char entero devuelvo true*/
	return (counter == 8);
}


void Broadcaster::addBit(short int bit) {
	Util::setBit(&broadcastBuffer,1,0,bit);
	counter++;
}
