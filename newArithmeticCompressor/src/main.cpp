/*
 * main.cpp
 *
 *  Created on: 24/06/2010
 *      Author: daniel
 */

#include <iostream>
#include <fstream>

#include "utils/const.h"
#include "Aritmetic.h"

int main(int argc,char **argv) {
	//La entrada de datos (no uso CIN porque me mete ruido)
	std::fstream message("entradaTest3.txt",std::fstream::in);
	std::fstream output("salidaTest3.txt",std::fstream::out);

	Aritmetic *aritmetic = new Aritmetic(NULL, &output,16,Aritmetic::COMPRESS,true);

	DistributionTable table;


	while(!message.eof()) {
		unsigned char c;
		message >> c;
		if(!message.eof()) {
			if(table.isCharacterInTable((charDT)c))
				table.updateFrequency(c);
			else
				table.addCharacter((charDT)c);
		}
		else
			table.addCharacter(C_EOF);
	}

	message.seekg(0,std::fstream::beg);
	message.close();

	message.open("entradaTest3.txt",std::fstream::in);

	Logger* log = Logger::getInstance();
	log->info("Test compresion");

	log->info("Tabla: ");
	log->info(table.toHuman());

	while(!message.eof()) {
		charDT c = (unsigned char)message.get();
		if(message.eof())
			c = C_EOF;

		aritmetic->compress(table,c);
	}

	delete aritmetic;

	output.seekg(0,std::fstream::beg);
	output.close();

	std::fstream input("salidaTest3.txt",std::fstream::in);
	aritmetic = new Aritmetic(&input, NULL,16,Aritmetic::UNCOMPRESS,false);

	charDT readChar = 0;
	log->info("=====================================================================");
	log->info("Test Descompresion");

	std::cout << "MENSAJE ORIGINAL:" << std::endl;

	while(readChar != C_EOF) {
		readChar = aritmetic->uncompress(table);
		if(readChar != C_EOF)
			std::cout << (char)readChar;
	}


	delete aritmetic;
	return 0;

}
