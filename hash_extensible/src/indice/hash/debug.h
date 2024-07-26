/*
 * debug.h
 *
 *  Created on: 24/10/2009
 *      Author: leonardo
 */

#ifndef DEBUG_H_
#define DEBUG_H_

#include <string>
#include <iostream>
using namespace std;

class Debug {
public:
	Debug();
	virtual ~Debug();
	void write(string);
	void writeln(string);
};

#endif /* DEBUG_H_ */
