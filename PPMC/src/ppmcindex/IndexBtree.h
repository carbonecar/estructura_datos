#ifndef IndexBtree_h
#define IndexBtree_h

#include "Index.h"
#include <string>
#include "../BPlusTree/BPlusTree.h"
#include "../exceptions/PPMCExceptions.h"
#include "../exceptions/ElementNotFoundException.h"
#include "../exceptions/OverflowException.h"
#include "../exceptions/ElementAlreadyExists.h"
#include "../Persistence/exceptions/PersistExceptions.h"

using namespace std;

class IndexBtree : public Index {

private:
	BPlusTree* bplusTree;
public:
	/**
	 * Construye el indice bTree con el tamanno de buffer que tiene
	 * la configuracion y el nombre que se le pasa mas un sufijo del tipo de indice que tiene.
	 * NO se debe pasar la extension del archivo dado que el IndexBtree la agrega
	 */
	IndexBtree(string filename);

	virtual ~IndexBtree();

protected:

	void insertIndexStructure(string context,DistributionTable* dt);

	string findInIndexStructre(string context);

	void modifyInIndexStructure(string prevContext, DistributionTable* dt);

	void structureToHuman();
	void structureToHuman(int blockNumber);

};

#endif // IndexBtree_h
