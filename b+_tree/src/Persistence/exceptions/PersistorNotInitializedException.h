/*
 * PersistorNotInitializedException.h
 *
 *  Created on: Apr 11, 2010
 *      Author: daniel
 */

#ifndef PERSISTORNOTINITIALIZEDEXCEPTION_H_
#define PERSISTORNOTINITIALIZEDEXCEPTION_H_

#include <exception>

class PersistorNotInitializedException : public std::exception {
public:
	PersistorNotInitializedException() throw();
	virtual ~PersistorNotInitializedException() throw();
	const char* what() const throw();
};

#endif /* PERSISTORNOTINITIALIZEDEXCEPTION_H_ */
