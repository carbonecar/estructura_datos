/*
 * HelpOption.cpp
 *
 */

#include "HelpOption.h"

int HelpOption::execute(char** argv){
	std::cout << argv[0] << " <nombre de archivo> -[IMQBS]" << std::endl;
	std::cout << " Descripción: " << std::endl;
	std::cout << " El formato de los valores a ingresares '(clave<entero>;valor<texto>)', el ingreso es realizado por entrada estandar" << std::endl;;
	std::cout << " -I	Ingresa un elemento a la esctructura." << std::endl;
	std::cout << " -M 	Modificar un elemento existente en la esctructura" << std::endl;
	std::cout << " -Q 	Quita un elemento existente en la esctructura" << std::endl;
	std::cout << " -S 	Muestra la esctructura actual." << std::endl;
	std::cout << " -H 	Esta descripción." << std::endl;
	return 0;
}

void HelpOption::action(){}
