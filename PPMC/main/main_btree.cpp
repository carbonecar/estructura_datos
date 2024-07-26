#include "../src/main/btree/PPMC_BTree.h"

int main(int argc, char** argv){

	PPMC_BTree* myMain = new PPMC_BTree();
	myMain->mainPPMC(argc,argv);

	delete myMain;

	return 0;
}
