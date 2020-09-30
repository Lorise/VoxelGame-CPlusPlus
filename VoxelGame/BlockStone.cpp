#include "BlockStone.h"

BlockId BlockStone::GetBlockId()
{
	return BLOCKID_STONE;
}

TextureBlockID BlockStone::GetTextureLeftId()
{
	return TEXTUREID_STONE;
}

TextureBlockID BlockStone::GetTextureRightId()
{
	return TEXTUREID_STONE;
}

TextureBlockID BlockStone::GetTextureTopId()
{
	return TEXTUREID_STONE;
}

TextureBlockID BlockStone::GetTextureBottomId()
{
	return TEXTUREID_STONE;
}

TextureBlockID BlockStone::GetTextureFrontId()
{
	return TEXTUREID_STONE;
}

TextureBlockID BlockStone::GetTextureBackId()
{
	return TEXTUREID_STONE;
}

bool BlockStone::isSolid()
{
	return true;
}
