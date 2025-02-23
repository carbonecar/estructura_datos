/*
 * TextIndex.h
 *
 */
#ifndef BUCKET_H_
#define BUCKET_H_

#include "../Persistence/Block.h"
#include "../utils/types.h"
#include "HashExceptions.h"
#include "../aritmetic/DistributionTable.h"
#include <iostream>
#include <string>
#include <map>
using namespace std;

class Bucket:public Block {
protected:
	unsigned int _limit;
	float _insertSizeLimit;
	unsigned int depth;
	map <Key, string> _elements;

	bool insertable(Key ,string);
	bool modificable(string, string);
	bool exist (Key);
public:
	Bucket();
	Bucket(unsigned int);
	virtual ~Bucket();

	void insert (Key , string);
	string find (Key);
	bool deleteKey (Key);
	bool modify (Key, string);

	void setInsertionSizeLimit(float);

	unsigned int countElements();

	string serialize();
	void unserialize(string &buffer);
	int getDataSize();
	void toHuman();

	map <Key, string>::iterator begin(){
		return _elements.begin();
	}
	map <Key, string>::iterator end(){
			return _elements.end();
	}
    unsigned int getDepth() const{return depth; }
    void setDepth(unsigned int depth){this->depth = depth;}

};

#endif /* BUCKET_H_ */
