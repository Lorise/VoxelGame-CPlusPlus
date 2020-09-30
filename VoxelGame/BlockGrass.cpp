#include "BlockGrass.h"

BlockId BlockGrass::GetBlockId()
{
	return BLOCKID_GRASS;
}

TextureBlockID BlockGrass::GetTextureLeftId()
{
	return TEXTUREID_GRASS_SIDE;
}

TextureBlockID BlockGrass::GetTextureRightId()
{
	return TEXTUREID_GRASS_SIDE;
}

TextureBlockID BlockGrass::GetTextureTopId()
{
	return TEXTUREID_GRASS;
}

TextureBlockID BlockGrass::GetTextureBottomId()
{
	return TEXTUREID_DIRT;
}

TextureBlockID BlockGrass::GetTextureFrontId()
{
	return TEXTUREID_GRASS_SIDE;
}

TextureBlockID BlockGrass::GetTextureBackId()
{
	return TEXTUREID_GRASS_SIDE;
}

bool BlockGrass::isSolid()
{
	return true;
}
