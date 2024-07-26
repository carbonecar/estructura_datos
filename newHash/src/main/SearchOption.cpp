/*
 * SearchOption.cpp
 *
 */

#include "SearchOption.h"

void SearchOption::action(){
	try{
		std::string tmp = dir->find(this->key);
		std::cout << "Se encontró (" << this->key << ";" << tmp << ")." << std::endl;
	}catch(...){
		std::cout << "Registro inexistente de" << this->key<< "." << std::endl;
	}
}
