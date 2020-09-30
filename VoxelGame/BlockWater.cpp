#include "BlockWater.h"

BlockId BlockWater::GetBlockId()
{
	return BLOCKID_WATER;
}

TextureBlockID BlockWater::GetTextureLeftId()
{
	return TEXTUREID_WATER;
}

TextureBlockID BlockWater::GetTextureRightId()
{
	return TEXTUREID_WATER;
}

TextureBlockID BlockWater::GetTextureTopId()
{
	return TEXTUREID_WATER;
}

TextureBlockID BlockWater::GetTextureBottomId()
{
	return TEXTUREID_WATER;
}

TextureBlockID BlockWater::GetTextureFrontId()
{
	return TEXTUREID_WATER;
}

TextureBlockID BlockWater::GetTextureBackId()
{
	return TEXTUREID_WATER;
}

bool BlockWater::isSolid()
{
	return true;
}
