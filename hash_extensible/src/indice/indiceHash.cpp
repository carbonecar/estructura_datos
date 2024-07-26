/*
 * estrategiaindicehash.cpp
 *
 *      Author: leonardo
 */

#include "indiceHash.h"

IndiceHash::IndiceHash(string filename)
{
	string fdir = filename;
	string fbuk = filename;
	fdir.append(".dir");
	fbuk.append(".bk");

	this->directory = new Directorio (fdir,fbuk,2048);
}

IndiceHash::IndiceHash(string filename, unsigned int maxKeys)
{
	string fdir = filename;
	string fbuk = filename;
	fdir.append(".dir");
	fbuk.append(".bk");

	this->directory = new Directorio (fdir,fbuk,maxKeys);
}


IndiceHash::~IndiceHash()
{
	this->directory->guardar();
	delete this->directory;
}

bool IndiceHash::exists (int key)
{
	return this->directory->exists(key);
}

bool IndiceHash::modify (int key, string data)
{
	return this->directory->modificar(key, data);
}

string IndiceHash::find (int key)
{
	return this->directory->buscar(key);
}

bool IndiceHash::add (int clave, string registro)
{
	//Insertar
	bool result = this->directory->insertar(clave,registro);
	return result;
}

bool IndiceHash::remove (int clave)
{
	//Eliminar
	bool result = this->directory->eliminar(clave);
	return result;
}
