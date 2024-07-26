/*
 * directorio.h
 *
 *  Created on: 24/10/2009
 *      Author: leonardo
 */

#ifndef DIRECTORIO_H_
#define DIRECTORIO_H_

#include <string>
#include <vector>
#include "textindex.h"					//Internal
#include "debug.h"						//Internal
#include "cubo.h"						//Internal
#include "funcionhash.h"				//Internal
#include "debug.h"						//Internal
#include "../../almacenamiento/LennyArchivo.h"				//External

using namespace std;

class Directorio:protected cFuncionHash{
protected:
	unsigned int _profundidad;
	Cubo * _cuboActual;
	unsigned int _maxClavesPorCubo;

	LennyArchivo* dirfile;
	LennyArchivo* bktfile;

	vector<unsigned int> _cubo;

	unsigned int guardarCubo (Cubo*);
	bool cargarCubo (Cubo*, unsigned int );

	int encontrar (int);

	friend class Cubo;

	int duplicarTabla ();
	int achicarTabla ();
	bool eliminarCubo (int, int );
	bool insertarCubo (int, int , int );
	int buscarHueco ();

	void cargar();

	Debug * _debug;
	void writeDebug (string);



public:
	Directorio(string, string, unsigned int);
	virtual ~Directorio();

	bool insertar (int, string);
	bool eliminar (int);
	string buscar (int);
	bool exists(int);
	bool modificar (int, string);

	void setDebug(Debug * dbg);
	void guardar();

	//string informe(compoReg* clave);
	string informe();
};

#endif /* DIRECTORIO_H_ */
