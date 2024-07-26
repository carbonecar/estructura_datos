/*
 * StadisticsTestCase.cpp
 *
 *  Created on: Jun 26, 2010
 *      Author: carlos
 */

#include "StadisticsTestCase.h"
#include "../../compresor/EstadisticCounter.h"
StadisticsTestCase::StadisticsTestCase() {}

void StadisticsTestCase::runtTest() {
	EstadisticCounter est;
	est.setFinalFilesize(100);
	est.setOriginalFilesize(10000);

	est.addContextHit("a");
	est.addContextHit("a");
	est.addContextHit("ab");
	est.addContextHit("ab");

	cout<<est<<endl;
}

StadisticsTestCase::~StadisticsTestCase() {}
