#pragma once
#include "BlockId.h"
#include "TextureBlockId.h"

class Block
{
public:
	virtual BlockId GetBlockId() = 0;

	virtual TextureBlockID GetTextureLeftId() = 0;
	virtual TextureBlockID GetTextureRightId() = 0;
	virtual TextureBlockID GetTextureTopId() = 0;
	virtual TextureBlockID GetTextureBottomId() = 0;
	virtual TextureBlockID GetTextureFrontId() = 0;
	virtual TextureBlockID GetTextureBackId() = 0;

	virtual bool isSolid() = 0;
};