#include "Background.h"
#include "Window.h"
#include "../VoxelGame/GameEngine.h"

namespace lib
{
	Background::Background( const LPDIRECT3DTEXTURE9 texture )
	{
		_sprite = new Sprite( D3DXVECTOR2( 0, 0 ), Window::get_width(), Window::get_height(), texture );
	}

	Background::~Background()
	{
		SafeDeletePtr( _sprite );
	}

	void Background::Render() const
	{
		D3DXMATRIX world;
		D3DXMatrixIdentity( &world );
		g_engine->core->d3dd9->SetTransform( D3DTS_WORLD, &world );

		_sprite->Render();
	}

	void Background::Update() const
	{
		_sprite->SetWidth( Window::get_width() );
		_sprite->SetHeight( Window::get_height() );
	}

	void Background::SetTexture( const LPDIRECT3DTEXTURE9 texture ) const
	{
		_sprite->SetTexture( texture );
	}
}
