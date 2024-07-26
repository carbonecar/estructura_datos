/*
 * FileNotFoundexception.h
 *
 *  Created on: 06/04/2010
 *      Author: sergio
 */

#ifndef FILENOTFOUNDEXCEPTION_H_
#define FILENOTFOUNDEXCEPTION_H_

#include <exception>

class FileNotFoundexception : public std::exception {
public:
	FileNotFoundexception() throw();
	virtual ~FileNotFoundexception() throw();
	const char* what() const throw();
};

#endif /* FILENOTFOUNDEXCEPTION_H_ */
