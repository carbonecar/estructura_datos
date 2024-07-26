/*
 * StatisticsOption.h
 */

#ifndef STATISTICSOPTION_H_
#define STATISTICSOPTION_H_

#include "Option.h"
#include <iostream>
#include <fstream>
using namespace std;
class StatisticsOption: public Option {
public:
	StatisticsOption();
	virtual ~StatisticsOption();
	int execute(char**);
	void action();
};

#endif /* STATISTICSOPTION_H_ */
