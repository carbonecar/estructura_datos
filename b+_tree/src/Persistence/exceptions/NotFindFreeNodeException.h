/*
 * NotFindFreeNodeException.h
 *
 *  Created on: 14/04/2010
 *      Author: sergio
 */

#ifndef NOTFINDFREENODEEXCEPTION_H_
#define NOTFINDFREENODEEXCEPTION_H_

#include <exception>

class NotFindFreeNodeException : public std::exception{
public:
	NotFindFreeNodeException() throw();
	virtual ~NotFindFreeNodeException() throw();
};

#endif /* NOTFINDFREENODEEXCEPTION_H_ */
