#include "BlockGold.h"

BlockId BlockGold::GetBlockId()
{
	return BLOCKID_GOLD;
}

TextureBlockID BlockGold::GetTextureLeftId()
{
	return TEXTUREID_GOLD;
}

TextureBlockID BlockGold::GetTextureRightId()
{
	return TEXTUREID_GOLD;
}

TextureBlockID BlockGold::GetTextureTopId()
{
	return TEXTUREID_GOLD;
}

TextureBlockID BlockGold::GetTextureBottomId()
{
	return TEXTUREID_GOLD;
}

TextureBlockID BlockGold::GetTextureFrontId()
{
	return TEXTUREID_GOLD;
}

TextureBlockID BlockGold::GetTextureBackId()
{
	return TEXTUREID_GOLD;
}

bool BlockGold::isSolid()
{
	return true;
}
