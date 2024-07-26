/*
 * FailFileWriteException.h
 *
 *  Created on: 07/04/2010
 *      Author: sergio
 */

#ifndef FAILFILEWRITEEXCEPTION_H_
#define FAILFILEWRITEEXCEPTION_H_

#include <exception>

class FailFileWriteException : public std::exception {
public:
	FailFileWriteException() throw();
	virtual ~FailFileWriteException() throw();

	const char* what() const throw();
};

#endif /* FAILFILEWRITEEXCEPTION_H_ */
