/*
 * PersistorInitializedException.cpp
 *
 *  Created on: 10/04/2010
 *      Author: sergio
 */

#include "PersistorInitializedException.h"

PersistorInitializedException::PersistorInitializedException() throw() {

}

PersistorInitializedException::~PersistorInitializedException() throw() {
}
const char* PersistorInitializedException::what() const throw(){
	return "Persistor ya iniciado.";
}
