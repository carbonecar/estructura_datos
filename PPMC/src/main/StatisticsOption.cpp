/*
 * StatisticsOption.cpp
 */

#include "StatisticsOption.h"


StatisticsOption::StatisticsOption() {}

StatisticsOption::~StatisticsOption() {}

int StatisticsOption::execute(char** argv){
	std::ifstream archivo;
	archivo.open("statics.txt");
	string line;
	while(!archivo.eof()){
		getline(archivo,line);
		cout<<line<<endl;
	}
	archivo.close();
	return 0;
}

void StatisticsOption::action(){}
