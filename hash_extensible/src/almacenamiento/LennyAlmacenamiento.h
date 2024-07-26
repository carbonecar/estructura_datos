/*
 * LennyAlmacenamiento.h
 *
 *  Created on: 27-oct-2009
 *      Author: leonardo
 */

#ifndef LENNYALMACENAMIENTO_H_
#define LENNYALMACENAMIENTO_H_

#include <string>
using namespace std;


class LennyAlmacenamiento{
protected:
	unsigned int _componentSize;

public:
	LennyAlmacenamiento();
	virtual ~LennyAlmacenamiento();

	virtual string leer (unsigned int)=0;			//Lee la posicion especificada (posicion = numero de componente)
	virtual unsigned int agregar (string)=0;			//Agrega un componente al final del archivo
	virtual void escribir (string, unsigned int)=0;	//Escribe en la posicion indicada (posicion = numero de componente)
	virtual void eliminar (unsigned int)=0;			//Marca un bloque como eliminado
	virtual bool cached (unsigned int)=0;			//Verifica si un componente está en cache
	virtual void flush()=0;							//Tira la cadena
	virtual unsigned int elementos() = 0;
	unsigned int getComponentSize()			//Obtiene el tamaño del componente
	{
		return this->_componentSize;
	};


};

#endif /* LENNYALMACENAMIENTO_H_ */
