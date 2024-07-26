/**
 * Main Logger
 * author nazareno
 */
#include "Logger.h"

#include <string>
#include <iostream>
#include <strings.h>

using namespace std;

enum Tarea {BUSCAR, INGRESAR, VOLCAR ,AYUDA, INDEFINIDO};

/*Numero maximo de registros por archivo de log*/
#define cantRegistros 10

int main(int argc, char **argv){

	Logger* log = Logger::getInstance(cantRegistros);
	Tarea task = INDEFINIDO;
	string key = "";

	if (argc == 2){
		if ( strcasecmp(argv[1], "-h")==0 )	task = AYUDA;
		if ( strcasecmp(argv[1], "-b")==0 )	task = BUSCAR;
		if ( strcasecmp(argv[1], "-i")==0 )	task = INGRESAR;
		if ( strcasecmp(argv[1], "-s")==0 )	task = VOLCAR;
	}

	if (task == INDEFINIDO)
	{
		cout << "No especificó ningún comando o el comando es incorrecto. Pruebe con -h" << endl;
		return -1;
	}

	if (task == AYUDA)
	{
		cout <<" -B => Esta opcion habilita la consola para recibir palabra/s a buscar. " << endl;
		cout <<" -I => Habilita la consola para ingresar nuevas entradas al archivo de log" << endl;
		cout <<"	-I -B soportan entradas masivas por cin." << endl;
		cout <<" -S => lista los registros del logger" << endl;
		cout <<" -H => Esta descripcion" << endl;
		cout <<"quit=> Opcion para salir de la aplicacion" << endl;
		return 0;
	}

	//Ciclo mientras tenga datos en la entrada estandar
	string linea = "";
	while (cin && linea.compare("quit")) {
		switch (task) {
		case BUSCAR:
			getline(cin, linea);
			if(linea.compare("quit") && linea.compare(""))
				log->buscar(linea);
			break;
		case INGRESAR:
			getline(cin, linea);
			if (linea.compare("quit"))
				log->insert(key, linea);
			break;
		case VOLCAR:
			if (linea.compare("quit")){
				log->listar();
			}
			return 0;
			break;
		default:
			break;
		}
	}

	return 0;
}
