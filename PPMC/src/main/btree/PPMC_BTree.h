#ifndef PPMC_BTree_h
#define PPMC_BTree_h

#include "../MainPPMC.h"
#include "../../ppmcindex/IndexBtree.h"


/**
 * Crea el indice que encapsula el btre
 */
class PPMC_BTree : public MainPPMC {

public:
	PPMC_BTree();
	virtual ~PPMC_BTree();
	Index* createIndex(string filename);

protected:
	/**
	 * Crea la opcion para ver los datos.
	 */
	Option* createDataOption(int blockNumber,string filename);
    Option* DataOption(string filename);
    Option* statistincsOption();
};

#endif // PPMC_BTree_h
