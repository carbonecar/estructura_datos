/*
 * Block.cpp
 *
 *  Created on: Apr 10, 2010
 *      Author: Daniel
 */

#include "Block.h"

Block::Block() {
	offset = -1;
}

Block::~Block() {
}

Offset Block::getOffset(){
	return offset;
}

void Block::setOffset(Offset offset){
	this->offset = offset;
}

