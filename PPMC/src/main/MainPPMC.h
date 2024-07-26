#ifndef MainPPMC_h
#define MainPPMC_h

#include "../ppmcindex/Index.h"
#include "Option.h"
#include "UndifenedOption.h"
#include "HelpOption.h"
#include "CompressionOption.h"
#include "DecompressionOption.h"

/**
 * Encapsula el algoritmo de compresión de PPMC
 */
class MainPPMC {
private:
	Option* option;

public:
	MainPPMC();
	int mainPPMC(int argc, char** argv);
    virtual Index* createIndex(string filename)=0;
    virtual ~MainPPMC();

protected:

	/**
	 * Crea la opcion para ver los datos.
	 */
    virtual Option* createDataOption(int blockNumber,string filename)=0;
    virtual Option* DataOption(string filename)=0;
    virtual Option* statistincsOption()=0;

};

#endif // MainPPMC_h
