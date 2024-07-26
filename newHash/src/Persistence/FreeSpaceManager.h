/*
 * FreeSpaceManager.h
 *
 */

#ifndef FREESPACEMANAGER_H_
#define FREESPACEMANAGER_H_

#include <string.h>

#include "../utils/types.h"
#include "Archivo.h"

#define PIVOTE 128
#define EMPTY 255
#define BLOCK_SIZE 5
#define HEADER_SIZE 512

class FreeSpaceManager {
private:
	std::string bitMap;
	Offset currentFreeSpaceBlock;
	int usedBlockCount;
	Archivo freeSpaceFile;

	void createFreeBlock();
	void saveBitMap();
	void loadBitMap(Offset offset);

public:
	FreeSpaceManager(std::string fileName);
	virtual ~FreeSpaceManager();

	void push(Offset offset);
	Offset pop() throw();
	bool isBlockUsed(Offset offset);
	int getUseBlockCount();
};

#endif /* FREESPACEMANAGER_H_ */
