/*
 * PersistorNotInitializedException.cpp
 *
 *  Created on: Apr 11, 2010
 *      Author: daniel
 */

#include "PersistorNotInitializedException.h"

PersistorNotInitializedException::PersistorNotInitializedException() throw() {

}

PersistorNotInitializedException::~PersistorNotInitializedException() throw() {
}

const char* PersistorNotInitializedException::what() const throw() {
	return "El persistor no se ha inicializado correctamente.";
}
