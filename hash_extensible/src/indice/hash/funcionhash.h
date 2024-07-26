/*
 * funcionhash.h
 *
 *  Created on: 24/10/2009
 *      Author: leonardo
 */

#ifndef FUNCIONHASH_H_
#define FUNCIONHASH_H_

#include <string>
#include "../../utiles/utiles.h"
using namespace std;

class cFuncionHash {
public:
	cFuncionHash();
	virtual ~cFuncionHash();

	int Hash (string key);
	int MakeAddress(string, unsigned int);
	int MakeAddress(int, unsigned int);
};

#endif /* FUNCIONHASH_H_ */
