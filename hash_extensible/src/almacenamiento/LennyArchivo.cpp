/*
 * LennyArchivo.cpp
 *
 *  Created on: 18/10/2009
 *      Author: leonardo
 */

#include "LennyArchivo.h"
#include <stdio.h>
#include "../utiles/excepciones.h"
#include <stdio.h>
#include <string.h>

LennyArchivo::LennyArchivo(string fileName, unsigned int componentSize) {
	this->_componentSize = componentSize;
	this->_filename = fileName;
	this->_fp = NULL;

	//Abro el archivo para trabajar ( y si no existe, lo creo)
	this->_fp = fopen (fileName.c_str(),"rb+");
	if (this->_fp == NULL) this->_fp = fopen (fileName.c_str(),"wb+");
	if (this->_fp == NULL)	throw except::ExceptionNotFound();
}

LennyArchivo::~LennyArchivo() {
	// TODO Auto-generated destructor stub
	if (this->_fp != NULL) fclose(this->_fp);
}

void LennyArchivo::mover (unsigned int componente)
{
	unsigned int pos = this->_componentSize * componente;
	fseek(this->_fp,pos,SEEK_SET);
}

string LennyArchivo::leer (unsigned int elem)
{
	//Si busco un componente que no existe, tiro excepcion
	if(elem >= this->elementos()) throw except::ExceptionOutOfRange();

	//Me muevo al componente
	this->mover(elem);

	//Leo componentSize bytes
	char* temp = new char[this->_componentSize];
	unsigned int leidos = 0;
	leidos = fread(temp,1,this->_componentSize,this->_fp);

	//Armo el string, borro el temporal, y devuelvo lo leido
	string sblock(temp,leidos);
	delete temp;
	return sblock;
}

void LennyArchivo::escribir (string data, unsigned int componente)
{
	//Si busco un componente que no existe, tiro excepcion
	//if(elem >= this->elementos()) throw except::ExceptionOutOfRange();

	//Relleno con 0 en caso de que lo que quiero escribir sea mas chico que el tamaño del componente
	if (data.size() < this->_componentSize )
	{
		unsigned int diferencia = this->_componentSize - data.size();
		string foo (diferencia,'\0');
		data.append(foo);
	}

	this->mover(componente);
	unsigned int escritos = 0;
	escritos = fwrite (data.c_str(),1,data.size(),this->_fp);

	if (escritos != data.size()) throw except::ExceptionWriteError();

}

unsigned int LennyArchivo::elementos()
{
	return (unsigned int)(this->size() / this->_componentSize);
}

unsigned int LennyArchivo::size()
{
	long pos = ftell (this->_fp);
	unsigned int size;

	//Me muevo al final del archivo y tomo el numero
	fseek (this->_fp, 0, SEEK_END);
	size=ftell (this->_fp);

	//Me muevo a donde estaba y devuelvo el tamaño
	fseek(this->_fp,pos,SEEK_SET);

	return size;
}

unsigned int LennyArchivo::agregar (string data)
{
	unsigned int respuesta = this->elementos();
	this->escribir(data,this->elementos());
	return respuesta;
}

void LennyArchivo::vaciar()
{
	fclose(this->_fp);
	remove(this->_filename.c_str());
	this->_fp = fopen (this->_filename.c_str(),"rb+");
	if (this->_fp == NULL) this->_fp = fopen (this->_filename.c_str(),"wb+");
	if (this->_fp == NULL)	throw except::ExceptionNotFound();

}

void LennyArchivo::flush()
{
	fflush (this->_fp);
}

bool LennyArchivo::cached (unsigned int block)
{
	//Jamas algo que esta en disco puede tener algo cacheado
	return false;
}
