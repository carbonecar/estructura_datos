#ifndef INDICE_H_
#define INDICE_H_

#include <string>

using namespace std;

class Indice
{
public:
	Indice();
	virtual ~Indice();
	
	/*Devuelve un offset (nro de registro o bloque en un archivo) si existe la clave
	o -1 si no existe la clave*/

	virtual string find (int)=0;					//Buscar
	virtual bool add (int, string)=0;			//Insertar
	virtual bool remove (int)=0;				//Eliminar
	virtual bool modify (int, string)=0;		//Modificar

};

#endif /*INDICE_H_*/
