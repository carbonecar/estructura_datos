/**
 * Hash extensible
 *
 */


#include <string>
#include <iostream>
#include <strings.h>
#include "indice/indiceHash.h"
#include "utiles/utiles.h"

using namespace std;

enum Tarea {BUSCAR, INGRESAR, MODIFICAR, QUITAR, VOLCAR, AYUDA, INDEFINIDO};
struct CmdParam
{
	int	key;
	string data;
};


const unsigned int __BLOCKSIZE__ = 1024;


CmdParam parseParam (string param)
{
	CmdParam result;
	result.key = 0;
	result.data = "" ;

	param = param.substr(1,param.size()-2);
	int p = param.find(';',0);
	if (p > 0)	//Tengo el ;!
	{
		string temp = param.substr(0,p);
		if (temp.size()>0) result.key=Util::toInt(temp);
		result.data = param.substr(p+1);
	}
	return result;
}


int main(int argc, char **argv)
{
	Tarea task = INDEFINIDO;

	if ((argc == 2) && ( strcasecmp(argv[1], "-h")==0))	task = AYUDA;
	if ((argc == 3) && ( strcasecmp(argv[2], "-s")==0))	task = VOLCAR;
	if ((argc == 3) && ( strcasecmp(argv[2], "-b")==0))	task = BUSCAR;
	if ((argc == 3) && ( strcasecmp(argv[2], "-i")==0))	task = INGRESAR;
	if ((argc == 3) && ( strcasecmp(argv[2], "-m")==0))	task = MODIFICAR;
	if ((argc == 3) && ( strcasecmp(argv[2], "-q")==0))	task = QUITAR;

	//---------------------------------------------------------------------
	if (task == INDEFINIDO)
	{
		cout << "Error, no especificó ningún comando. Pruebe con -h" << endl;
		return -1;
	}

	//---------------------------------------------------------------------
	if (task == AYUDA)
	{
		cout <<" <arch> -B 	buscar" << endl;
		cout <<" <arch> -I 	ingresar" << endl;
		cout <<" <arch> -M 	modificar" << endl;
		cout <<" <arch> -Q 	quitar" << endl;
		cout <<" <arch> -S 	volcar" << endl;
		cout <<" -H 		ayuda" << endl;
		return 0;
	}
	//---------------------------------------------------------------------
	if (task == VOLCAR)
	{
		IndiceHash Hash (argv[1],__BLOCKSIZE__);
		cout << Hash.informe() << endl;
		return 0;
	}
	//---------------------------------------------------------------------


	//Abro el índice hash
	IndiceHash Hash (argv[1],__BLOCKSIZE__);

	//Ciclo mientras tenga datos en la entrada estandar
	string linea="";
	while (cin)
	{
		//Obtengo una linea. Formato: (clave;[posicion])
		getline(cin, linea);

		if (linea.empty()) continue;
		//Obtengo un par (clave; posicion)
		CmdParam parametro = parseParam (linea);

		//Segun la tarea, tengo que hacer algo
		switch (task) {
			case BUSCAR:
				if (Hash.exists(parametro.key))
				{
					cout << "No encontré el registro con clave " << parametro.key << endl;
				} else {
					cout << "Encontré (" << parametro.key << ";" << Hash.find(parametro.key) << ")" << endl;
				}

				break;

			case INGRESAR:
				if (Hash.add(parametro.key,parametro.data))
				{
					cout << linea << " agregado correctamente" << endl;
				} else {
					cout << "No se pudo agregar el registro " << linea << endl;
				}
				break;

			case MODIFICAR:
				if (Hash.modify(parametro.key, parametro.data))
				{
					cout << "No se pudo modificar el registro con clave " << parametro.key << endl;
				} else {
					cout << "Registro modificado correctamente " << linea << endl;
				}

				break;

			case QUITAR:
				if (Hash.remove(parametro.key))
				{
					cout << "No se pudo eliminar el registro con clave " << parametro.key << endl;
				} else {
					cout << "Registro con clave " << parametro.key << " ha sido eliminado"<< endl;
				}
				break;

			default:
				break;
		}

	}

	return 0;
}
