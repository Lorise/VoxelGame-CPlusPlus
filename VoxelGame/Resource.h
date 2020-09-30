#pragma once
#include "Headers.h"
#include "TextureBlockId.h"
#include "UiTextureId.h"

class Resource
{
public:
	static HRESULT Load();

	static LPDIRECT3DTEXTURE9 GetBlockTextureFromId( TextureBlockID id );
	static LPDIRECT3DTEXTURE9 GetGuiTextureFromId( UiTextureId id );

	static void Cleanup();

private:
	static LPDIRECT3DTEXTURE9 LoadTexture( std::string filename );
	static HRESULT LoadBlockTexture();
	static HRESULT LoadGuiTexture();

	static std::map< TextureBlockID, LPDIRECT3DTEXTURE9 > _texturesBlock;
	static std::map< UiTextureId, LPDIRECT3DTEXTURE9 > _textureGui;
};