#include "BlockIron.h"

BlockId BlockIron::GetBlockId()
{
	return BLOCKID_IRON;
}

TextureBlockID BlockIron::GetTextureLeftId()
{
	return TEXTUREID_IRON;
}

TextureBlockID BlockIron::GetTextureRightId()
{
	return TEXTUREID_IRON;
}

TextureBlockID BlockIron::GetTextureTopId()
{
	return TEXTUREID_IRON;
}

TextureBlockID BlockIron::GetTextureBottomId()
{
	return TEXTUREID_IRON;
}

TextureBlockID BlockIron::GetTextureFrontId()
{
	return TEXTUREID_IRON;
}

TextureBlockID BlockIron::GetTextureBackId()
{
	return TEXTUREID_IRON;
}

bool BlockIron::isSolid()
{
	return true;
}
