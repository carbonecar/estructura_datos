/*
 * Block.cpp
 *
 */

#include "Block.h"

Block::Block() {
	offset = 0;
}

Block::~Block() {
}

Offset Block::getOffset(){
	return offset;
}

void Block::setOffset(Offset offset){
	this->offset = offset;
}

