/*
 * FileNotFoundexception.cpp
 *
 *  Created on: 06/04/2010
 *      Author: sergio
 */

#include "FileNotOpenException.h"

FileNotOpenException::FileNotOpenException() throw() {
	// TODO Auto-generated constructor stub

}

FileNotOpenException::~FileNotOpenException() throw() {
	// TODO Auto-generated destructor stub
}

const char* FileNotOpenException::what() const throw(){
	return "El archivo no está abierto";
}


