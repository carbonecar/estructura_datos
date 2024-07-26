/*
 * UndifenedOption.cpp
 *
 */

#include "UndifenedOption.h"

int UndifenedOption::execute(char**){
	std::cout << "No especificó ningún comando o el comando es incorrecto." << std::endl;
	std::cout << "Pruebe con -h. " << std::endl;
	return -1;
}

void UndifenedOption::action(){}
