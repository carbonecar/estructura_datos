/*
 * Context.cpp
 *
 *  Created on: 09/06/2010
 *      Author: leonardo
 */

#include "Context.h"
#include "../exceptions/PPMCExceptions.h"
#include "../utils/const.h"
#include <exception>

Index * Context::index = NULL;

Context::Context(unsigned int maxOrder){
	this->maxOrder = maxOrder;
	this->currentContext = "";
}

Context::~Context()
{
	//if (Context::index != NULL) delete Context::index;
}

string Context::getStringContext()
{
	return this->currentContext;
}

unsigned int Context::getMaxOrder()
{
	return this->maxOrder;
}

void Context::push (char c)
{
	if (this->getCurrentOrder() == this->maxOrder)
	{
		this->currentContext.erase(0,1);
	}

	this->currentContext.append(1,c);

	//Si no existe el contexto lo crea y le agrega el escape
	if(!this->index->contextExists(currentContext))
		this->addCharacter(C_ESC);
}

unsigned int Context::getCurrentOrder()
{
	return this->currentContext.size();
}

void Context::previousContext()
{
	//TODO: agregar la excepcion que corresponde y arreglarlo en PPMC.cpp
	if (this->currentContext.size() == 0) throw new std::exception();
	if (this->currentContext.size() == 1)
	{
		this->currentContext = "";
	} else {
		this->currentContext = this->currentContext.substr(1,this->currentContext.size());
		//Si no existe el contexto lo crea y le agrega el escape
		if(!this->index->contextExists(currentContext))
			this->addCharacter(C_ESC);
	}
}

Context * Context::clone()
{
	Context * ctx = new Context(this->maxOrder);
	ctx->currentContext = this->currentContext;
	return ctx;
}

void Context::setIndex (Index * index)
{
	Context::index = index;
}

void Context::updateContext (charDT c)
{
	if (Context::index == NULL) throw new std::exception ();
	try
	{
		Context::index->updateContext(c, this->getStringContext());

	} catch (PPMCExceptions::ContextNotFoundException * E) {
		delete E;
		Context::index->addCharacter(C_ESC,this->getStringContext());
		Context::index->addCharacter(c,this->getStringContext());
	}
}

void Context::addCharacter (charDT c)
{
	Context::index->addCharacter(c, this->getStringContext());
}

DistributionTable * Context::getDistributionTable()
{
	if (Context::index == NULL) throw new std::exception ();
	DistributionTable * dt = NULL;
	try
	{
		dt = Context::index->getContext(this->getStringContext());

	} catch (PPMCExceptions::ContextNotFoundException * E) {
		delete E;
		Context::index->addCharacter(C_ESC, this->getStringContext());
		dt = Context::index->getContext(this->getStringContext());
	}
	return dt;
}

Context & Context::operator= (Context & ctx)
{
	this->maxOrder = ctx.maxOrder;
	this->currentContext = ctx.currentContext;
	return *this;
}

void Context::toHuman()
{
	Context::index->toHuman();
}
