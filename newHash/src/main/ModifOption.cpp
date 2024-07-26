/*
 * ModifOption.cpp
 *
 */

#include "ModifOption.h"

void ModifOption::action(){
	try{
		bool result = dir->modify(this->key, this->value);
		if (!result){
			std::cout << "No encuentro el registro con clave " << this->key << std::endl;
		} else {
			std::cout << "Registro modificado (" << this->key <<";"<< this->value << ")." <<std::endl;
		}
	}catch(HashExceptions::ElementNotFoundException* e){
		std::cout << "(" << this->key <<";"<< this->value << ") ya existe en el indice." << std::endl;
		delete e;
	}catch(HashExceptions::ExtendedSizeException* e){
		std::cout << this->value << " => cadena supera el espacio del indice." << std::endl;
		delete e;
	}
}
