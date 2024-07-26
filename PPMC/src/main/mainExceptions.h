/**
 * Excepciones de las estrategias del main
 */


#ifndef MAINEXCEPTIONS_H_
#define MAINEXCEPTIONS_H_

#include <exception>

namespace mainExceptions{
	class FailInputFormatException: public std::exception {};
}

#endif /* MAINEXCEPTIONS */
