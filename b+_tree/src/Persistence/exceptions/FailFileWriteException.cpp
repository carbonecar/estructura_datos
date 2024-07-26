/*
 * FailFileWriteException.cpp
 *
 *  Created on: 07/04/2010
 *      Author: sergio
 */

#include "FailFileWriteException.h"

FailFileWriteException::FailFileWriteException() throw() {

}

FailFileWriteException::~FailFileWriteException() throw() {
}

const char* FailFileWriteException::what() const throw(){
	return "No se pudo escribir correctamente el registro";
}
