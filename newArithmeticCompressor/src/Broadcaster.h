/*
 * Broadcaster.h
 *
 *  Created on: 20/06/2010
 *      Author: daniel
 */

#ifndef BROADCASTER_H_
#define BROADCASTER_H_

#include <iostream>
#include <string>

class Broadcaster {
private:
	unsigned char broadcastBuffer;
	unsigned int counter;

	std::ostream * output;

    /* guarda bloques del tamaño de un int en el archivo */
    void saveBroadcast();

    /* valida que si el tamaño del string es igual a un int baja los datos al archivo */
    bool isBroadcastFull();

    /* agrega un bit a la tira de broadcast */
    void addBit(short int bit);

public:
	Broadcaster(std::ostream * output);
	virtual ~Broadcaster();

	/* emite el bit recibido 0 o 1 */
	void broadcast(short int bit);

	/* emite una cadena de bist */
	void broadcast(std::string bits);

	/* guarda lo que queda en un archivo */
	void closeOutput();
};

#endif /* BROADCASTER_H_ */
