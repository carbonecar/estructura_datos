/*
 * LennyArchivo.h
 *
 *  Created on: 18/10/2009
 *      Author: leonardo
 */

#ifndef LENNYARCHIVO_H_
#define LENNYARCHIVO_H_

#include <string>
#include "LennyAlmacenamiento.h"

using namespace std;

class LennyArchivo:public LennyAlmacenamiento {
protected:
	string _filename;
	void mover (unsigned int);		//Seek
	FILE* _fp;

public:
	LennyArchivo(string, unsigned int);
	virtual ~LennyArchivo();

	string leer (unsigned int);				//Lee la posicion especificada (posicion = numero de componente)
	unsigned int agregar (string);			//Agrega un componente al final del archivo
	void escribir (string, unsigned int);	//Escribe en la posicion indicada (posicion = numero de componente)
	void eliminar (unsigned int) {};			//Marca un bloque como eliminado
	virtual unsigned int elementos();		//Cantidad de elementos en el archivo
	unsigned int size();						//Tamaño en bytes del archivo
	void vaciar();								//Toma un archivo y lo vuelve a longitud cero
	virtual void flush();
	virtual bool cached (unsigned int);

};

#endif /* LENNYARCHIVO_H_ */
