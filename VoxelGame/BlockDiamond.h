#pragma once
#include "Block.h"
#include "BlockId.h"

class BlockDiamond : public Block
{
public:
	BlockId GetBlockId();

	TextureBlockID GetTextureLeftId();
	TextureBlockID GetTextureRightId();
	TextureBlockID GetTextureTopId();
	TextureBlockID GetTextureBottomId();
	TextureBlockID GetTextureFrontId();
	TextureBlockID GetTextureBackId();

	bool isSolid();
};