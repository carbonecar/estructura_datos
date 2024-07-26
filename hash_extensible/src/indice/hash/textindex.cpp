/*
 * textindex.cpp
 *
 *  Created on: 24/10/2009
 *      Author: leonardo
 */
#include "../../utiles/utiles.h"
#include "textindex.h"

cTextIndex::cTextIndex()
{
	this->_elemento.clear();
	this->_limitado = false;
	this->_limite = 0;
	this->_debug = NULL;
}

cTextIndex::cTextIndex(unsigned int limite)
{
	this->_elemento.clear();
	this->_limitado = true;
	this->_limite = limite;
	this->_debug = NULL;
}

cTextIndex::~cTextIndex()
{

	this->_elemento.clear();
}


unsigned int cTextIndex::elementos()
{
	return this->_elemento.size();
}

bool cTextIndex::insertable(int key, string value)
{
	if (! this->_limitado) return true;

	string result = "";
	for (map<int, string>::iterator it = this->_elemento.begin() ; it != this->_elemento.end() ; ++it)
	{
		result.append(Util::SerializeInt(it->first));
		result.append(Util::SerializeString(it->second));
	}
	result.append(Util::SerializeInt(key));
	result.append(Util::SerializeString(value));
	unsigned int tam = result.size() + 2*sizeof(int) +1;

	return (tam < this->_limite);
	//return (elementos<this->_limite);
}

bool cTextIndex::modificable(int key, string value)
{
	if (! this->_limitado) return true;

	string result = "";
	string dataOrig = "";
	for (map<int, string>::iterator it = this->_elemento.begin() ; it != this->_elemento.end() ; ++it)
	{
		if (it->first == key) dataOrig = it->second;
		result.append(Util::SerializeInt(it->first));
		result.append(Util::SerializeString(it->second));
	}
	result.append(Util::SerializeInt(key));
	result.append(Util::SerializeString(value));
	unsigned int tam = result.size() + 2*sizeof(int) +1;
	tam = tam + value.size() - dataOrig.size();

	return (tam < this->_limite);

}

bool cTextIndex::insertar (int key, string value)
{
	//Si no puedo instertar devuelvo falso y salgo
	if (! this->insertable(key, value) ) return false;
	if (this->existe(key)) return false;

	this->_elemento.insert ( pair <int,string>(key, value));
	return true;
}

bool cTextIndex::modificar (int key, string data)
{
	if (!this->existe(key)) return false;
	if (! this->modificable(key, data)) return false;
	this->_elemento.erase(key);
	this->_elemento.insert ( pair <int,string>(key, data));
	return true;
}

string cTextIndex::buscar (int key)
{
	map<int,string>::iterator it;
	it = this->_elemento.find(key);
	return it->second;
}

bool cTextIndex::eliminar (int key)
{
	if (! this->existe(key)) return false;
	int elementos = this->_elemento.erase(key);
	return (elementos != 0);
}

bool cTextIndex::existe (int key)
{
	map<int,string>::iterator it, fin;
	fin = this->_elemento.end();
	it = this->_elemento.find(key);
	return (it != fin);
}

void cTextIndex::setLimitado (bool limitado)
{
	this->_limitado = limitado;
}

void cTextIndex::setLimite(unsigned int limite)
{
	this->_limite = limite;
}


void cTextIndex::setDebug(Debug * dbg)
{
	this->_debug = dbg;
}

void cTextIndex::writeDebug (string data)
{
	if (this->_debug != NULL) this->_debug->writeln(data);
}

int cTextIndex::getClave(unsigned int pos)
{
	if (pos >= this->elementos()) return -1;

	map<int, string>::iterator it = this->_elemento.begin();
	for (unsigned j = 0 ; j != pos ; ++j) ++it;
	return it->first;
}

string cTextIndex::getReg(unsigned int pos)
{
	if (pos >= this->elementos()) return 0;

	map<int, string>::iterator it = this->_elemento.begin();
	for (unsigned j = 0 ; j != pos ; ++j) ++it;
	return it->second;
}

/*
string cTextIndex::toHuman(compoReg * clave)
{
	string result ="";
	result.append("Elementos: "); result.append(Util::toString(this->elementos()));result.append("\n");
	for (map<string, unsigned int>::iterator it = this->_elemento.begin() ; it != this->_elemento.end() ; ++it)
	{
		string cc = it->first;
		clave->deserializar(cc);

		result.append(clave->toHuman()); result.append(" => "); result.append(Util::toString(it->second));result.append("\n");
	}
	result.append("\n");

	return result;
}
*/

string cTextIndex::toHuman()
{
	string result ="";
	result.append("Elementos: "); result.append(Util::toString(this->elementos()));result.append("\n");
	for (map<int, string>::iterator it = this->_elemento.begin() ; it != this->_elemento.end() ; ++it)
	{
		int cc = it->first;
		result.append(Util::toString(cc)); result.append(" => "); result.append(it->second);result.append("\n");
	}
	result.append("\n");

	return result;
}
