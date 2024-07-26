/*
 * UndifenedOption.cpp
 *
 */

#include "UndifenedOption.h"

int UndifenedOption::execute(char**){
	std::cout << "No especificó ningún comando. " << std::endl;
	std::cout << "Pruebe con -h. " << std::endl;
	return -1;
}

void UndifenedOption::action(){}
