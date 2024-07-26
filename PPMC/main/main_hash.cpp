#include "../src/main/hash/PPMC_Hash.h"

int main(int argc, char** argv){

	PPMC_Hash* myMain=new PPMC_Hash;
	myMain->mainPPMC(argc,argv);

	delete myMain;
}
