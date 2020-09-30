#include "BlockAir.h"

BlockId BlockAir::GetBlockId()
{
	return BLOCKID_AIR;
}

TextureBlockID BlockAir::GetTextureLeftId()
{
	return TEXTUREID_NOTEXTURE;
}

TextureBlockID BlockAir::GetTextureRightId()
{
	return TEXTUREID_NOTEXTURE;
}

TextureBlockID BlockAir::GetTextureTopId()
{
	return TEXTUREID_NOTEXTURE;
}

TextureBlockID BlockAir::GetTextureBottomId()
{
	return TEXTUREID_NOTEXTURE;
}

TextureBlockID BlockAir::GetTextureFrontId()
{
	return TEXTUREID_NOTEXTURE;
}

TextureBlockID BlockAir::GetTextureBackId()
{
	return TEXTUREID_NOTEXTURE;
}

bool BlockAir::isSolid()
{
	return false;
}
