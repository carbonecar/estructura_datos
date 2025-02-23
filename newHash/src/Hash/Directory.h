/*
 * directorio.h
 *
 */

#ifndef DIRECTORY_H_
#define DIRECTORY_H_

#include "Table.h"					//Internal
#include "Bucket.h"						//Internal
#include "HashFunction.h"				//Internal
#include "../Persistence/PersistorBase.h"	//External
#include "../utils/types.h"	//External

#include <vector>
#include <string>
using namespace std;

#define BUFFERTABLE 512
#define LIMIT_TABLE 64

class Directory{
private:
	PersistorBase* dirFile;
	PersistorBase* bktFile;

	Table* table;
	Bucket * bucketActual;
	unsigned int depth;
	unsigned int maxBucketSize;
    float insertionSizeLimit;

	void setDepth();

	void duplicateTable (unsigned int pos,Offset offset);
	void reduceTable ();
	void replaceTable(Offset,Offset);
    unsigned int findPosofTable(Key);
    void organizeBuckets(Bucket*);
    void tryCombine(unsigned int);
    void redistributeTable(Bucket * auxBucket, unsigned int pos);
public:
    Directory(string, unsigned int);
    virtual ~Directory();
	void setInsertionSizeLimit(float);

    bool insert(Key, string);
    bool remove(Key);
    bool modify(Key, string);
    string find(Key);
    void inform();
};

#endif /* DIRECTORIO_H_ */
