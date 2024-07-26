#ifndef IndexHash_h
#define IndexHash_h

#include "Index.h"
#include "../Hash/Directory.h"
#include "../utils/types.h"
#include "../Hash/HashExceptions.h"
#include "../exceptions/PPMCExceptions.h"
#include "../Persistence/exceptions/PersistExceptions.h"

//#define _BUCKETSIZE_ 4194304
#define _BUCKETSIZE_ 4096

class IndexHash : public Index {
private:
	Directory* directory;
public:
	IndexHash(string);

	virtual ~IndexHash();


protected:
	void insertIndexStructure(string context,DistributionTable* dt);

	string findInIndexStructre(string context);

	void modifyInIndexStructure(string prevContext, DistributionTable* dt);

	void structureToHuman();
	void structureToHuman(int blockNumber);
};

#endif // IndexHash_h
