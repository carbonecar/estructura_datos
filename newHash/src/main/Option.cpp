/*
 * Option.cpp
 *
 */

#include "Option.h"
#include "mainExceptions.h"

const char* FileName = "config.txt";

Option::Option() {
	this->configFile = new ConfigFile(FileName);
	this->dir = NULL;
}

Option::Option(char** argv) {
	this->configFile = new ConfigFile(FileName);
	dir= new Directory(argv[1],configFile->read<unsigned int>("blockSize"));
	dir->setInsertionSizeLimit(configFile->read<float>("chargePercent"));
}

Option::~Option() {
	delete configFile;
	if (dir != NULL)
		delete dir;
}

void Option::parser(std::string line){

	this->key = 0;
	this->value = "" ;

	int open = line.find('(',0);
	int close = line.find(')',0);
	int div = line.find(';',0);

	if (open != 0 || (unsigned)close != line.size()-1 || div == -1)
		throw mainExceptions::FailInputFormatException();

	open++;
	std::stringstream temp;
	temp << line.substr(open,div-open);
	if (temp.str().size() > 0) temp >> this->key;
	else throw mainExceptions::FailInputFormatException();

	div++;
	this->value.append(line.substr(div,close-div));
}

int Option::execute(char** argv){
	std::string line="";
	/*
	 * Ciclo: mientras tenga datos en la entrada estandar
	 */
	while (! std::cin.eof()){
		getline(std::cin, line);

		if (line.empty()) continue;
		try{
			this->parser(line);
			action();
		}catch(...){
			std::cout << "Formato de cadena incorrecto: "<< line << std::endl;
		}
	}
	return 0;
}
