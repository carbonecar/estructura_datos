/*
 * PersistorInitializedException.h
 *
 *  Created on: 10/04/2010
 *      Author: sergio
 */

#ifndef PERSISTORINITIALIZEDEXCEPTION_H_
#define PERSISTORINITIALIZEDEXCEPTION_H_

#include <exception>

class PersistorInitializedException : public std::exception  {
public:
	PersistorInitializedException() throw();
	virtual ~PersistorInitializedException() throw();
	const char* what() const throw();
};

#endif /* PERSISTORINITIALIZEDEXCEPTION_H_ */
