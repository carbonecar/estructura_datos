/*
 * textindex.h
 *
 *  Created on: 24/10/2009
 *      Author: leonardo
 */
#include <string>
#include <map>
#include "debug.h"
//#include "../../compoReg/compoReg.h"

using namespace std;

#ifndef TEXTINDEX_H_
#define TEXTINDEX_H_

class cTextIndex {
protected:
	bool	_limitado;
	unsigned int _limite;
	unsigned int elementos();
	bool insertable(int, string);
	bool modificable (int, string);
	map <int,string> _elemento;
	Debug * _debug;

public:
	cTextIndex();
	cTextIndex(unsigned int);
	virtual ~cTextIndex();

	bool insertar (int, string);
	string buscar (int);
	bool eliminar (int);
	bool existe (int);
	bool modificar (int, string);

	void setLimitado (bool);
	void setLimite(unsigned int);

	void setDebug(Debug * dbg);
	void writeDebug (string);

	int getClave (unsigned int);
	string getReg(unsigned int);

	string toHuman();
	//string toHuman(compoReg * clave);
};

#endif /* TEXTINDEX_H_ */
