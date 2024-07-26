/*
 * DeleteOption.cpp
 *
 */

#include "DeleteOption.h"
#include "../Hash/HashExceptions.h"

void DeleteOption::action(){
	try{
		dir->remove(this->key);
		std::cout << "Registro con clave " << this->key << " ha sido eliminado"<< std::endl;
	}catch (HashExceptions::ElementNotFoundException* e){
		std::cout << "No se pudo eliminar el registro con clave " << this->key << std::endl;
		delete e;
	}
}


