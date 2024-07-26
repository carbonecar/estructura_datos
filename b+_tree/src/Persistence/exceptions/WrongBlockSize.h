/*
 * WrongBlockSize.h
 *
 *  Created on: 16/04/2010
 *      Author: sergio
 */

#ifndef WRONGBLOCKSIZE_H_
#define WRONGBLOCKSIZE_H_

#include <exception>

class WrongBlockSize: public std::exception {
public:
	WrongBlockSize() throw();
	virtual ~WrongBlockSize() throw();
};

#endif /* WRONGBLOCKSIZE_H_ */
