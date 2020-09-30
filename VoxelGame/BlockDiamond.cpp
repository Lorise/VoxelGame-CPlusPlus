#include "BlockDiamond.h"

BlockId BlockDiamond::GetBlockId()
{
	return BLOCKID_DIAMOND;
}

TextureBlockID BlockDiamond::GetTextureLeftId()
{
	return TEXTUREID_DIAMOND;
}

TextureBlockID BlockDiamond::GetTextureRightId()
{
	return TEXTUREID_DIAMOND;
}

TextureBlockID BlockDiamond::GetTextureTopId()
{
	return TEXTUREID_DIAMOND;
}

TextureBlockID BlockDiamond::GetTextureBottomId()
{
	return TEXTUREID_DIAMOND;
}

TextureBlockID BlockDiamond::GetTextureFrontId()
{
	return TEXTUREID_DIAMOND;
}

TextureBlockID BlockDiamond::GetTextureBackId()
{
	return TEXTUREID_DIAMOND;
}

bool BlockDiamond::isSolid()
{
	return true;
}
