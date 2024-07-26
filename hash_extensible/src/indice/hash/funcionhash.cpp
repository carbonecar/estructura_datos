/*
 * funcionhash.cpp
 *
 *  Created on: 24/10/2009
 *      Author: leonardo
 */

#include "funcionhash.h"
#include <string.h>
#include "../../utiles/utiles.h"

cFuncionHash::cFuncionHash() {}

cFuncionHash::~cFuncionHash() {}

int cFuncionHash::Hash (string clave)
{

    int sum = 0;
    int len = clave.size();
    if (len % 2 == 1) len++;
    for(int j=0; j<len; j+=2)
       sum = (sum +100 + clave[j] + clave[j+1])%19937;

    return sum;
}

int cFuncionHash::MakeAddress (string key, unsigned int depth)
{
	//
	//Funcion original
	int retval = 0;
    int mask = 1;
    int hashVal = Hash(key);
    int lowbit = 0;
    for(unsigned int j = 0; j < 16 ; j++)
    {
       retval = retval << 1;
       lowbit = hashVal & mask;
       retval = retval | lowbit;
       hashVal = hashVal >> 1;
    }
    unsigned int tam = 1 << depth;
    retval = retval % tam;
    return retval;
	//

	/*/Version nueva
    unsigned int i = 0;
    int hash = 0;
    int sub = 0;
    int remainder = 0;
    hash = Hash(key);
	for(i=0; i < depth; i++)
	{
	  sub = sub << 1;
      remainder = hash%2;
      sub = sub + remainder;
      hash = hash >> 1;
    }
   return sub;
	*/
}

int cFuncionHash::MakeAddress(int key, unsigned int depth)
{
	//return cFuncionHash::MakeAddress(Util::toString(key),depth);

	unsigned int valor = 1 << depth;
	return (key % valor);
}
