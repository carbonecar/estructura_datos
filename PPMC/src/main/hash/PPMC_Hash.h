#ifndef PPMC_Hash_h
#define PPMC_Hash_h

#include "../MainPPMC.h"
#include "../../ppmcindex/IndexHash.h"

/**
 * Encapsula la creacion del indice
 */
class PPMC_Hash : public MainPPMC {

public:
	PPMC_Hash();

	virtual Index* createIndex(string filename);
	virtual ~PPMC_Hash();

protected:
	/**
	 * Crea la opcion para ver los datos.
	 */
	Option* createDataOption(int blockNumber,string filename);
    Option* DataOption(string filename);
    Option* statistincsOption();
};

#endif // PPMC_Hash_h
