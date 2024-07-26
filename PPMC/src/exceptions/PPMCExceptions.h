/*
 * PPMCExceptions.h
 *
 *  Created on: 19/06/2010
 *      Author: sergio
 */

#ifndef PPMCEXCEPTIONS_H_
#define PPMCEXCEPTIONS_H_

#include <exception>

namespace PPMCExceptions {
	class ContextNotFoundException : public std::exception{};
	class CharacterNotFoundException : public std::exception{};
	class EmptyContextException : public std::exception{};
}

#endif /* PPMCEXCEPTIONS_H_ */
