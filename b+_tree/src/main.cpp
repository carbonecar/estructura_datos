/**
 * Main BPlussTree
 *
 */

#include "BPlusTree/BPlusTree.h"
#include "BPlusTree/Element.h"
#include "BPlusTree/BNode.h"
#include "utils/ConfigurationMananger.h"
#include <string>
#include <iostream>
#include <strings.h>
#include "BPlusTree/MainTree.h"
#include "test/BPlusTreeTest.h"
#include "test/TestConfigurationManager.h"
using namespace std;



int main(int argc, char **argv) {
	/*string deleteFile = "del ";
		   deleteFile.append(argv[1]);
	system(deleteFile.c_str());
	string deleteFile2 = "del ";
		   deleteFile2.append(argv[1]);
		   deleteFile2.append(".fs");
	system(deleteFile2.c_str());*/

	MainTree mainTree;
	return mainTree.run(argc,argv);
	//TestConfigurationManager testCFM;
	//testCFM.runTest();
	/*for(int i=0; i < 30000; i++) {
		std::cout<<"("<<i<<";"<<"asdf"<<")"<<endl;
	}*/
	//BPlusTreeTest bplusTreeTest;
	//bplusTreeTest.run();
	//return 0;

}



