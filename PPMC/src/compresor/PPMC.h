#ifndef PPMC_h
#define PPMC_h

#include "../aritmetic/Arithmetic.h"
#include "../aritmetic/DistributionTable.h"
#include "../ppmcindex/Index.h"
#include "Context.h"
#include "../logger/Logger.h"
#include "EstadisticCounter.h"

#include <string>
#include <iostream>
using namespace std;
class PPMC {

 public:

     PPMC(int presicion, int ordenMax, bool loggear,bool loggearAritmetic);
     virtual ~PPMC();

     void setRootContext(DistributionTable*);

     void compress(istream * entrada, ostream * salida, bool exclusion);

     void unCompress(istream * entrada, ostream * salida, bool exclusion);

     void estadistict();

     int getPresicion();

     int getOrdenMax();

     void setIndex(Index* index);


private:
     void updateContext(Context * currentContext, charDT charUnCompress, unsigned int countESC);

 	 int presicion;
 	 int ordenMax;
 	 DistributionTable * rootContext;
 	 Logger* logger;
 	 bool loggear;
 	 bool loggearAritmetic;
 	 EstadisticCounter * estadisticCounter;

     void log(charDT c);
     void log(std::string message);

};

#endif // PPMC_h
