#include "BlockCoal.h"

BlockId BlockCoal::GetBlockId()
{
	return BLOCKID_COAL;
}

TextureBlockID BlockCoal::GetTextureLeftId()
{
	return TEXTUREID_COAL;
}

TextureBlockID BlockCoal::GetTextureRightId()
{
	return TEXTUREID_COAL;
}

TextureBlockID BlockCoal::GetTextureTopId()
{
	return TEXTUREID_COAL;
}

TextureBlockID BlockCoal::GetTextureBottomId()
{
	return TEXTUREID_COAL;
}

TextureBlockID BlockCoal::GetTextureFrontId()
{
	return TEXTUREID_COAL;
}

TextureBlockID BlockCoal::GetTextureBackId()
{
	return TEXTUREID_COAL;
}

bool BlockCoal::isSolid()
{
	return true;
}
