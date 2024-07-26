#ifndef Index_h
#define Index_h

#include <assert.h>
#include <string>
#include <iostream>
#include "../aritmetic/DistributionTable.h"
#include "../utils/types.h"
#include "../exceptions/ElementNotFoundException.h"
#include "../exceptions/PPMCExceptions.h"
#include "../utils/const.h"
#include "../Persistence/exceptions/PersistExceptions.h"



using namespace std;
class Index {

 public:
	Index();
	/**
	 * Devuelve NULL si el contexto no fue encontrados
	 */
    DistributionTable* getContext(string context);

    void updateContext(charDT character, string prevContext);

    void addCharacter (charDT character, string context);

    bool contextExists(string context);

    void toHuman();

    void toHuman(int blockNumber);

protected:
	virtual void insertIndexStructure(string context,DistributionTable* dt)=0;

	virtual string findInIndexStructre(string context)=0;

	virtual void modifyInIndexStructure(string prevContext, DistributionTable* dt)=0;

	virtual void structureToHuman()=0;
	virtual void structureToHuman(int blockNumber)=0;
};

#endif // Index_h
