/*
 * HelpOption.cpp
 *
 */

#include "HelpOption.h"

int HelpOption::execute(char** argv){
	std::cout << "Instrucción :" << std::endl;
	std::cout << "- Compresión / Descompresión :" << std::endl;
	std::cout << "---" << argv[0] << " -[cd] <orden> -f <archivo de trabajo> " << std::endl;
	std::cout << "--- Realiza la operación de compresión o descompresión en el orden seleccionado, usando la entrada de datos por Standar Input, y la salida es por Standar Output. " << std::endl;
	std::cout << std::endl;

	//TODO revisar como se hacen las estadisticas.
	std::cout << "- Estadisticas:" << std::endl;
	std::cout << "---" << argv[0] << " -e " << std::endl;
	std::cout << "--- Devuelve la información de los contextos utilizazados en la ultima operación . " << std::endl;
	std::cout << std::endl;

	std::cout << "- Ver los datos de un contexto:" << std::endl;
	std::cout << "---" << argv[0] << " -vv <número de bloque> -f <archivo de trabajo>" << std::endl;
	std::cout << "--- Muestra los datos del contexto seleccionado. " << std::endl;
	std::cout << std::endl;

	std::cout << "- Ver todos los datos:" << std::endl;
	std::cout << "---" << argv[0] << " -v -f <archivo de trabajo>" << std::endl;
	std::cout << "--- Muestra los datos de todos los contexto. " << std::endl;
	std::cout << std::endl;

	std::cout << "- Ayuda:" << std::endl;
	std::cout << "---" << argv[0] << " -h " << std::endl;
	std::cout << "--- Muestra esta descripción. " << std::endl;
	std::cout << std::endl;
	return 0;
}

void HelpOption::action(){}
