#include "Sprite.h"
#include "../VoxelGame/GameEngine.h"
#include "Vertex2.h"

namespace lib
{
	Sprite::Sprite( const D3DXVECTOR2 position, const int width, const int height, const LPDIRECT3DTEXTURE9 texture )
	{
		D3DXMatrixTranslation( &_position, position.x, position.y, 0 );
		_width = width;
		_height = height;
		_texture = texture;

		VERTEX2 v[] = {
			VERTEX2( 0.f, 0.f, 0.f, 0.f ),
			VERTEX2( static_cast< float >( _width ), 0.f, 1.f, 0.f ),
			VERTEX2( static_cast< float >( _width ), static_cast< float >( _height ), 1.f, 1.f ),
			VERTEX2( 0.f, static_cast< float >( _height ), 0.f, 1.f )
		};

		g_engine->core->d3dd9->CreateVertexBuffer( sizeof( v ) * sizeof( VERTEX2 ), NULL, VERTEX2::FVF, D3DPOOL_DEFAULT, &_vertexBuffer, nullptr );
		VERTEX2 *pVD;
		_vertexBuffer->Lock( NULL, NULL, reinterpret_cast< void** >( &pVD ), NULL );
		memcpy( pVD, v, sizeof( v ) );
		_vertexBuffer->Unlock();

		WORD index[] = { 0, 1, 2, 2, 3, 0 };

		g_engine->core->d3dd9->CreateIndexBuffer( sizeof( index ), NULL, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &_indexBuffer, nullptr );
		WORD *pID;
		_indexBuffer->Lock( NULL, NULL, reinterpret_cast< void** >( &pID ), NULL );
		memcpy( pID, index, sizeof( index ) );
		_indexBuffer->Unlock();
	}

	Sprite::~Sprite()
	{
		SafeRelease( _vertexBuffer );
		SafeRelease( _indexBuffer );
	}

	void Sprite::Render()
	{
		g_engine->core->camera->begin2_d();

		g_engine->core->d3dd9->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
		g_engine->core->d3dd9->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
		g_engine->core->d3dd9->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
		g_engine->core->d3dd9->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );

		g_engine->core->d3dd9->SetFVF( VERTEX2::FVF );
		g_engine->core->d3dd9->SetStreamSource( NULL, _vertexBuffer, NULL, sizeof( VERTEX2 ) );
		g_engine->core->d3dd9->SetIndices( _indexBuffer );
		g_engine->core->d3dd9->SetTexture( 0, _texture );

		D3DXMATRIX world;
		g_engine->core->d3dd9->GetTransform( D3DTS_WORLD, &world );
		g_engine->core->d3dd9->SetTransform( D3DTS_WORLD, &( _position * world ) );
		g_engine->core->d3dd9->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, NULL, NULL, 6, 0, 2 );

		g_engine->core->d3dd9->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE );

		g_engine->core->camera->end2_d();
	}

	void Sprite::SetPosition( const D3DXVECTOR2 position )
	{
		D3DXMatrixTranslation( &_position, position.x, position.y, 0 );
	}

	void Sprite::SetWidth( const int width )
	{
		_width = width;

		SafeRelease( _vertexBuffer );

		VERTEX2 v[] = {
			VERTEX2( 0.f, 0.f, 0.f, 0.f ),
			VERTEX2( static_cast< float >( _width ), 0.f, 1.f, 0.f ),
			VERTEX2( static_cast< float >( _width ), static_cast< float >( _height ), 1.f, 1.f ),
			VERTEX2( 0.f, static_cast< float >( _height ), 0.f, 1.f )
		};

		g_engine->core->d3dd9->CreateVertexBuffer( sizeof( v ), NULL, VERTEX2::FVF, D3DPOOL_DEFAULT, &_vertexBuffer, nullptr );
		VERTEX2 *pVD;
		_vertexBuffer->Lock( NULL, NULL, reinterpret_cast< void** >( &pVD ), NULL );
		memcpy( pVD, v, sizeof( v ) );
		_vertexBuffer->Unlock();
	}

	void Sprite::SetHeight( const int height )
	{
		_height = height;

		SafeRelease( _vertexBuffer );

		VERTEX2 v[] = {
			VERTEX2( 0.f, 0.f, 0.f, 0.f ),
			VERTEX2( static_cast< float >( _width ), 0.f, 1.f, 0.f ),
			VERTEX2( static_cast< float >( _width ), static_cast< float >( _height ), 1.f, 1.f ),
			VERTEX2( 0.f, static_cast< float >( _height ), 0.f, 1.f )
		};

		g_engine->core->d3dd9->CreateVertexBuffer( sizeof( v ), NULL, VERTEX2::FVF, D3DPOOL_DEFAULT, &_vertexBuffer, NULL );
		VERTEX2 *pVD;
		_vertexBuffer->Lock( NULL, NULL, reinterpret_cast< void** >( &pVD ), NULL );
		memcpy( pVD, v, sizeof( v ) );
		_vertexBuffer->Unlock();
	}

	void Sprite::SetTexture( LPDIRECT3DTEXTURE9 texture )
	{
		_texture = texture;
	}

	D3DXVECTOR2 Sprite::GetPosition() const
	{
		return D3DXVECTOR2( _position( 3, 0 ), _position( 3, 1 ) );
	}
	
	int Sprite::GetWidth() const
	{
		return _width;
	}

	int Sprite::GetHeight() const
	{
		return _height;
	}
}
