/*
 * cubo.h
 *
 *  Created on: 24/10/2009
 *      Author: leonardo
 */

#ifndef CUBO_H_
#define CUBO_H_

#include "textindex.h"
#include "funcionhash.h"

class Cubo: public cTextIndex, protected cFuncionHash{
public:
	Cubo(void* , unsigned int);
	virtual ~Cubo();

protected:
	int _direccion;
	unsigned int _profundidad;
	void * _dir;
	bool _del;

	friend class Directorio;

	bool insertar (int, string);
	bool eliminar (int);
	bool modificar (int, string);


	string serializar();
	void deserializar(string);

	bool intentarCombinar(unsigned int);

	Cubo* bananaSplit(unsigned int);
	void Redistribute (Cubo & newBucket);

	bool asNew(string data);
	//string toHuman(compoReg * clave);
	string toHuman();

};

#endif /* CUBO_H_ */
