/**
 * Hash extensible
 *
 */

#include "main/Option.h"
#include "main/UndifenedOption.h"
#include "main/HelpOption.h"
#include "main/ShowOption.h"
#include "main/SearchOption.h"
#include "main/InsertOption.h"
#include "main/ModifOption.h"
#include "main/DeleteOption.h"

int main(int argc, char** argv){

	Option* option = NULL;

	/**-------------------------------------------------------------------------
	 * Defino estrategia a seguir.
	 */
	switch(argc){
		case 2:
			if ( strcasecmp(argv[1], "-h") == 0 )
				{	option = new HelpOption(); break; }
		case 3:
			if ( strcasecmp(argv[2], "-s") == 0 )
				{	option = new ShowOption(argv);	break;	} else
			if ( strcasecmp(argv[2], "-b") == 0 )
				{	option = new SearchOption(argv);break;	} else
			if ( strcasecmp(argv[2], "-i") == 0 )
				{	option = new InsertOption(argv);break;	} else
			if ( strcasecmp(argv[2], "-m") == 0 )
				{	option = new ModifOption(argv);	break;	} else
			if ( strcasecmp(argv[2], "-q") == 0 )
				{	option = new DeleteOption(argv);break;	}
		default: option = new UndifenedOption();
	}
	/**-------------------------------------------------------------------------
	 * Ejecuto la estrategia.
	 */
	return option->execute(argv);
}
