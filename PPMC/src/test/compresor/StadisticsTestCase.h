/*
 * StadisticsTestCase.h
 *
 *  Created on: Jun 26, 2010
 *      Author: carlos
 */

#ifndef STADISTICSTESTCASE_H_
#define STADISTICSTESTCASE_H_

#include <cstdio>
#include <iostream>

using namespace std;

class StadisticsTestCase {
public:
	StadisticsTestCase();
	void runtTest();
	virtual ~StadisticsTestCase();
};

#endif /* STADISTICSTESTCASE_H_ */
