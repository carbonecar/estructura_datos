/*
 * estrategiaindicehash.h
 *
 *  Created on: 25/10/2009
 *      Author: leonardo
 */

#ifndef ESTRATEGIAINDICEHASH_H_
#define ESTRATEGIAINDICEHASH_H_

#include "indice.h"
#include "hash/directorio.h"

class IndiceHash: public Indice {
protected:
	Directorio * directory;

public:
	IndiceHash(string filename);						//Recibe el nombre del archivo de DATOS!!
	IndiceHash(string filename, unsigned int);		//Recibe el nombre del archivo de DATOS y el tamaño del bloque!!
	virtual ~IndiceHash();


	virtual string find (int);							//Buscar
	virtual bool add (int, string);					//Insertar
	virtual bool remove (int);						//Eliminar
	virtual bool modify (int, string);				//Modificar
	virtual bool exists (int);


	//string informe (compoReg* clave) {return this->directory->informe(clave);}
	string informe () {return this->directory->informe();}
};

#endif /* ESTRATEGIAINDICEHASH_H_ */
