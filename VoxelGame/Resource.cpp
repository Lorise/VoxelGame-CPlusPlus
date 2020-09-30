#include "Resource.h"
#include "Directories.h"

std::map< TextureBlockID, LPDIRECT3DTEXTURE9 > Resource::_texturesBlock;
std::map< UiTextureId, LPDIRECT3DTEXTURE9 > Resource::_textureGui;

HRESULT Resource::Load()
{
	HRESULT hr;

	hr = LoadBlockTexture();
	if ( FAILED( hr ) )
	{
		Cleanup();
		MessageBox( nullptr, "LoadMapTexture", "Error load texture", MB_OK );
		return E_FAIL;
	}

	hr = LoadGuiTexture();
	if ( FAILED( hr ) )
	{
		Cleanup();
		MessageBox( nullptr, "LoadGuiTexture", "Error load texture", MB_OK );
		return E_FAIL;
	}

	return S_OK;
}

LPDIRECT3DTEXTURE9 Resource::LoadTexture( std::string filename )
{
	HRESULT hr;
	LPDIRECT3DTEXTURE9 texture = nullptr;

	hr = D3DXCreateTextureFromFileA( lib::g_engine->core->d3dd9, filename.c_str(), &texture );

	if ( FAILED( hr ) )
	{
		lib::SafeRelease( texture );
		MessageBox( nullptr, filename.c_str(), "Error D3DXCreateTextureFromFileA", MB_OK );
		return nullptr;
	}

	std::cout << "Load block texture: " << filename << std::endl;

	return texture;
}

HRESULT Resource::LoadBlockTexture()
{
	HRESULT hr;
	LPDIRECT3DTEXTURE9 texture = nullptr;

	texture = LoadTexture( DIRECTORIES::GameDir + DIRECTORIES::BlockTexture + "dirt.png" );
	_texturesBlock.insert( std::make_pair( TEXTUREID_DIRT, texture ) );

	texture = LoadTexture( DIRECTORIES::GameDir + DIRECTORIES::BlockTexture + "grass.png" );
	_texturesBlock.insert( std::make_pair( TEXTUREID_GRASS, texture ) );

	texture = LoadTexture( DIRECTORIES::GameDir + DIRECTORIES::BlockTexture + "grass_side.png" );
	_texturesBlock.insert( std::make_pair( TEXTUREID_GRASS_SIDE, texture ) );

	texture = LoadTexture( DIRECTORIES::GameDir + DIRECTORIES::BlockTexture + "stone.png" );
	_texturesBlock.insert( std::make_pair( TEXTUREID_STONE, texture ) );

	texture = LoadTexture( DIRECTORIES::GameDir + DIRECTORIES::BlockTexture + "cobblestone.png" );
	_texturesBlock.insert( std::make_pair( TEXTUREID_COBBLESTONE, texture ) );

	texture = LoadTexture( DIRECTORIES::GameDir + DIRECTORIES::BlockTexture + "coal.png" );
	_texturesBlock.insert( std::make_pair( TEXTUREID_COAL, texture ) );

	texture = LoadTexture( DIRECTORIES::GameDir + DIRECTORIES::BlockTexture + "iron.png" );
	_texturesBlock.insert( std::make_pair( TEXTUREID_IRON, texture ) );

	texture = LoadTexture( DIRECTORIES::GameDir + DIRECTORIES::BlockTexture + "gold.png" );
	_texturesBlock.insert( std::make_pair( TEXTUREID_GOLD, texture ) );

	texture = LoadTexture( DIRECTORIES::GameDir + DIRECTORIES::BlockTexture + "diamond.png" );
	_texturesBlock.insert( std::make_pair( TEXTUREID_DIAMOND, texture ) );

	texture = LoadTexture( DIRECTORIES::GameDir + DIRECTORIES::BlockTexture + "bedrock.png" );
	_texturesBlock.insert( std::make_pair( TEXTUREID_BEDROCK, texture ) );

	texture = LoadTexture( DIRECTORIES::GameDir + DIRECTORIES::BlockTexture + "water.png" );
	_texturesBlock.insert( std::make_pair( TEXTUREID_WATER, texture ) );

	return S_OK;
}

HRESULT Resource::LoadGuiTexture()
{
	HRESULT hr;
	LPDIRECT3DTEXTURE9 texture = nullptr;

	texture = LoadTexture( DIRECTORIES::GameDir + DIRECTORIES::GuiTexture + "cursor.png" );
	_textureGui.insert( std::make_pair( UITEXTUREID_CURSOR, texture ) );

	texture = LoadTexture( DIRECTORIES::GameDir + DIRECTORIES::GuiTexture + "button.png" );
	_textureGui.insert( std::make_pair( UITEXTUREID_BUTTON, texture ) );

	texture = LoadTexture( DIRECTORIES::GameDir + DIRECTORIES::GuiTexture + "select_button.png" );
	_textureGui.insert( std::make_pair( UITEXTUREID_BUTTON_ACTIVE, texture ) );

	texture = LoadTexture( DIRECTORIES::GameDir + DIRECTORIES::GuiTexture + "nactive_button.png" );
	_textureGui.insert( std::make_pair( UITEXTUREID_BUTTON_NACTIVE, texture ) );

	texture = LoadTexture( DIRECTORIES::GameDir + DIRECTORIES::GuiTexture + "widget.png" );
	_textureGui.insert( std::make_pair( UITEXTUREID_PANEL, texture ) );

	texture = LoadTexture( DIRECTORIES::GameDir + DIRECTORIES::GuiTexture + "selectitem.png" );
	_textureGui.insert( std::make_pair( UITEXTUREID_PANEL_SELECTOR, texture ) );

	texture = LoadTexture( DIRECTORIES::GameDir + DIRECTORIES::GuiTexture + "health.png" );
	_textureGui.insert( std::make_pair( UITEXTUREID_HEALTH, texture ) );
	
	texture = LoadTexture( DIRECTORIES::GameDir + DIRECTORIES::GuiTexture + "hunger.png" );
	_textureGui.insert( std::make_pair( UITEXTUREID_HUNGRY, texture ) );

	return S_OK;
}

LPDIRECT3DTEXTURE9 Resource::GetBlockTextureFromId( TextureBlockID id )
{
	return _texturesBlock[id];
}

LPDIRECT3DTEXTURE9 Resource::GetGuiTextureFromId( UiTextureId id )
{
	return _textureGui[id];
}

void Resource::Cleanup()
{
	for ( auto it = _texturesBlock.begin(); it != _texturesBlock.end(); ++it )
		lib::SafeRelease( it->second );
	_texturesBlock.clear();

	for ( auto it = _textureGui.begin(); it != _textureGui.end(); ++it )
		lib::SafeRelease( it->second );
	_textureGui.clear();
}