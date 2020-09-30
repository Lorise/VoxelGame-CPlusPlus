#include "BlockDirt.h"

BlockId BlockDirt::GetBlockId()
{
	return BLOCKID_DIRT;
}

TextureBlockID BlockDirt::GetTextureLeftId()
{
	return TEXTUREID_DIRT;
}

TextureBlockID BlockDirt::GetTextureRightId()
{
	return TEXTUREID_DIRT;
}

TextureBlockID BlockDirt::GetTextureTopId()
{
	return TEXTUREID_DIRT;
}

TextureBlockID BlockDirt::GetTextureBottomId()
{
	return TEXTUREID_DIRT;
}

TextureBlockID BlockDirt::GetTextureFrontId()
{
	return TEXTUREID_DIRT;
}

TextureBlockID BlockDirt::GetTextureBackId()
{
	return TEXTUREID_DIRT;
}

bool BlockDirt::isSolid()
{
	return true;
}
