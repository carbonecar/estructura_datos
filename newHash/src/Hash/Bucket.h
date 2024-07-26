/*
 * TextIndex.h
 *
 */
#ifndef BUCKET_H_
#define BUCKET_H_

#include "../Persistence/Block.h"
#include "../utils/types.h"
#include "HashExceptions.h"
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

	bool insertable(unsigned int ,string);
	bool modificable(string, string);
	bool exist (unsigned int);
public:
	Bucket();
	Bucket(unsigned int);
	virtual ~Bucket();

	void insert (unsigned int , string);
	string find (unsigned int);
	bool deleteKey (unsigned int);
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
