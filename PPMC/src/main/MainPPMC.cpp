#include "MainPPMC.h"
#include <string.h>
#include <assert.h>
MainPPMC::MainPPMC() {
	option = NULL;
}

int MainPPMC::mainPPMC(int argc, char** argv) {

	/**-------------------------------------------------------------------------
	 * Defino estrategia a seguir.
	 */
	switch (argc) {
	case 2:
		if (strcasecmp(argv[1], "-h") == 0)
			option = new HelpOption();
		else if (strcasecmp(argv[1], "-e") == 0)
			option = this->statistincsOption();

		break;

	case 4:
		if (strcasecmp(argv[1], "-v") == 0) {
			string filename = argv[3];
			option = this->DataOption(filename);
		}
		break;
	case 5:
		if (strcasecmp(argv[1], "-c") == 0) {
			if(atoi(argv[2]) == 0){
				std::cout << "Comando incorrecto. El orden ingresado no es un numero" << std::endl;
				return -1;
			}
			option = new CompressionOption(this);
		} else if (strcasecmp(argv[1], "-d") == 0) {
			if (atoi(argv[2]) == 0) {
				std::cout << "Comando incorrecto. El orden ingresado no es un numero" << std::endl;
				return -1;
			}
			option = new DecompressionOption(this);
		} else if (strcasecmp(argv[1], "-vv") == 0) {
			int nroBloque = atoi(argv[2]);
			string filename = argv[4];
			option = this->createDataOption(nroBloque, filename);
		}
		break;
	}
	if(option==NULL){
		option = new UndifenedOption();
	}

	/**-------------------------------------------------------------------------
	 * Ejecuto la estrategia.
	 */
	return option->execute(argv);
}

MainPPMC::~MainPPMC() {
	delete option;
}
