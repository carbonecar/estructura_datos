/*
 * HashFunction.cpp
 *
 */

#include "HashFunction.h"

int HashFunction::Hash (string key){
	//Esta función está deprecada
    int sum = 0;
    int len = key.size();
    if (len % 2 == 1) len++;
    for(int j=0; j<len; j+=2)
       sum = (sum +100 + key[j] + key[j+1])%19937;

    return sum;
}

int HashFunction::MakeAddress (string key, unsigned int depth){

	//Esta función está deprecada
    unsigned int i = 0;
    int hash = 0;
    int sub = 0;
    int remainder = 0;
    hash = Hash(key);
	for(i=0; i < depth; i++){
	  sub = sub << 1;
      remainder = hash%2;
      sub = sub + remainder;
      hash = hash >> 1;
    }
   return sub;
}

int HashFunction::MakeAddress(unsigned int key, unsigned int depth){
	//value tiene la cantidad de celdas de la tabla
	unsigned int value = 1 << depth;

	//Devuelve el resto de value y la cantida de celdas
	return (key % value);
}
