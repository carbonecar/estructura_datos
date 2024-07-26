/*
 * InsertOption.cpp
 *
 */

#include "InsertOption.h"
#include "../Hash/HashExceptions.h"

void InsertOption::action(){
	try{
		bool result = dir->insert(this->key, this->value);
		if (!result){
			std::cout << "No se pudo agregar el registro (" << this->key <<";"<< this->value << ")." << std::endl;
		} else {
			std::cout << "Agregado correctamente (" << this->key <<";"<< this->value << ")." << std::endl;
		}
	}catch(HashExceptions::ElementAlreadyExistsException* e){
		std::cout << "(" << this->key <<";"<< this->value << ") ya existe en el indice." << std::endl;
		delete e;
	}catch(HashExceptions::ExtendedSizeException* e){
		std::cout << this->value << " => cadena supera el espacio del indice." << std::endl;
		delete e;
	}
}


