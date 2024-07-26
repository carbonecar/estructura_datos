/*
 * TestAritmetic.cpp
 *
 *  Created on: 06/06/2010
 *      Author: daniel
 */

#include "TestAritmetic.h"
#include "../../utils/utiles.h"
#include "../../utils/const.h"
#include "../../aritmetic/DistributionTable.h"
#include "../../logger/Logger.h"

#include <string>
#include <iostream>

TestAritmetic::TestAritmetic() {

}

TestAritmetic::~TestAritmetic() {

}

void TestAritmetic::runTest() {
	//testCompression(9);
	//testUncompression(9);
	//testCompression2(13);
	//testUncompression2(13);
	testCompressTexto();
	//testBitFunctions();
}

void TestAritmetic::testCompression(unsigned int precision) {
	std::fstream output("salidaTest1.txt",std::fstream::out | std::fstream::binary);
	Arithmetic *aritmetic = new Arithmetic(NULL, &output,Arithmetic::COMPRESS,false);

	std::string message = "DIVIDIDOS";
	DistributionTable table;

	table.addCharacter('D',3);
	table.addCharacter('I',3);
	table.addCharacter('O',1);
	table.addCharacter('S',1);
	table.addCharacter('V',1);
	table.addCharacter(C_EOF,1);


	Logger* log = Logger::getInstance();
	log->info("Test compresion");
	log->info("Mensaje: DIVIDIDOS");


	for(unsigned int i = 0; i < message.size(); i++) {
		log->info("Paso: "  + Util::uIntToString(i) + " caracter: " + message[i]);
		aritmetic->compress((wchar_t)message[i],table);
	}
	aritmetic->compress(C_EOF,table);

	delete aritmetic;
}

void TestAritmetic::testUncompression(unsigned int precision) {
	std::fstream input("salidaTest1.txt",std::fstream::in | std::fstream::binary);
	Arithmetic *aritmetic = new Arithmetic(&input, NULL,Arithmetic::UNCOMPRESS,false);

	std::string message = "";
	DistributionTable table;

	table.addCharacter('D',3);
	table.addCharacter('I',3);
	table.addCharacter('O',1);
	table.addCharacter('S',1);
	table.addCharacter('V',1);
	table.addCharacter(C_EOF,1);

	charDT readChar = 0;

	Logger* log = Logger::getInstance();
	log->info("");
	log->info("Test descompresion");

	while(readChar != C_EOF) {
		readChar = aritmetic->uncompress(table);
		if(readChar != C_EOF)
			message.append(1,readChar);
	}
	log->info("Mensaje descomprimido: " + message);

	std::cout << message << std::endl;
	assert(message == "DIVIDIDOS");

	delete aritmetic;
}

void TestAritmetic::testCompression2(unsigned int precision) {
	//La entrada de datos (no uso CIN porque me mete ruido)
	std::fstream output("salidaTest2.txt",std::fstream::out);
	Arithmetic *aritmetic = new Arithmetic(NULL, &output,Arithmetic::COMPRESS,false);

	std::string message = "BAABCA";
	DistributionTable table;

	table.addCharacter('A',3);
	table.addCharacter('B',2);
	table.addCharacter('C',1);
	table.addCharacter(C_EOF,1);


	Logger* log = Logger::getInstance();
	log->info("Test compresion");
	log->info("Mensaje: " + message);


	for(unsigned int i = 0; i < message.size(); i++) {
		log->info("Paso: "  + Util::uIntToString(i) + " caracter: " + message[i]);
		aritmetic->compress(message[i],table);
	}
	aritmetic->compress(C_EOF,table);

	delete aritmetic;
}

void TestAritmetic::testUncompression2(unsigned int precision) {
	std::fstream input("salidaTest2.txt",std::fstream::in);
	Arithmetic *aritmetic = new Arithmetic(&input, NULL,Arithmetic::UNCOMPRESS,false);

	std::string message = "";
	DistributionTable table;

	table.addCharacter('A',3);
	table.addCharacter('B',2);
	table.addCharacter('C',1);
	table.addCharacter(C_EOF,1);

	charDT readChar = 0;

	Logger* log = Logger::getInstance();
	log->info("Test descompresion");

	while(readChar != C_EOF) {
		readChar = aritmetic->uncompress(table);
		if(readChar != C_EOF)
			message.append(1,readChar);
	}
	log->info("Mensaje descomprimido: " + message);

	assert(message == "BAABCA");

	delete aritmetic;
}

void TestAritmetic::testCompressTexto() {
	std::fstream message("entrada.txt",std::fstream::in | std::fstream::binary);
	std::fstream output("salidaTest3.txt",std::fstream::out | std::fstream::binary);

	Arithmetic *aritmetic = new Arithmetic(NULL, &output,Arithmetic::COMPRESS,true);

	DistributionTable table;

	for(charDT i = 0; i <= C_EOF ; i++)
		table.addCharacter(i,0);

	unsigned char c;
	while(!message.eof()) {
		c = message.get();
		if(!message.eof()) {
			if(table.isCharacterInTable((charDT)c))
				table.updateFrequency(c);
			else
				table.addCharacter((charDT)c);
		}else
			table.updateFrequency(C_EOF);
	}

	std::cout << table.toHuman() << std::endl;
	message.seekg(0,std::fstream::beg);
	message.close();

	message.open("entrada.txt",std::fstream::in | std::fstream::binary);

	Logger* log = Logger::getInstance();
	log->info("Test compresion");

	while(!message.eof()) {
		c = message.get();
		if(!message.eof())
			// c = C_EOF;

		aritmetic->compress(c,table);
	}
	aritmetic->compress(C_EOF,table);

	delete aritmetic;

	//output.seekg(0,std::fstream::beg);
	output.close();

	std::fstream input("salidaTest3.txt",std::fstream::in | std::fstream::binary);
	aritmetic = new Arithmetic(&input, NULL,Arithmetic::UNCOMPRESS,false);
	std::fstream testOutput("salidaDescomprimida.txt",std::fstream::out | std::fstream::binary);

	charDT readChar = 0;
	log->info("=====================================================================");
	log->info("Test Descompresion");

	std::cout << "MENSAJE ORIGINAL:" << std::endl;

	while(readChar != C_EOF) {
		readChar = aritmetic->uncompress(table);
		if(readChar != C_EOF)
			testOutput << (char)readChar;
	}


	delete aritmetic;

}

void TestAritmetic::testBitFunctions() {
	std::string bitsString = "1010";

	unsigned int number = Util::bitsStringToInt(bitsString);

	assert(number == 10);

	bitsString = Util::bitsIntToString(number,4);

	assert(bitsString == "1010");

}




