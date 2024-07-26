/*
 * FileNotFoundexception.cpp
 *
 *  Created on: 06/04/2010
 *      Author: sergio
 */

#include "FileNotFoundexception.h"

FileNotFoundexception::FileNotFoundexception() throw() {

}

FileNotFoundexception::~FileNotFoundexception() throw() {
}

const char* FileNotFoundexception::what() const throw(){
	return "El archivo no pudo ser abierto";
}


