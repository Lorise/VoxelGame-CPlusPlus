#pragma once
#include "functional.h"
#include "EnginePointers.h"

class cSprite
{
public:
	cSprite() = delete;
	cSprite( const D3DXVECTOR2 &position, const int &width, const int &height, const LPDIRECT3DTEXTURE9 &texture );
	~cSprite();

	virtual void Render();

	void SetPosition( const D3DXVECTOR2 &position );
	void SetWidth( const int &width );
	void SetHeight( const int &height );
	void SetTexture( const LPDIRECT3DTEXTURE9 &texture );

	D3DXVECTOR2 GetPosition() const;
	const int& GetWidth() const;
	const int& GetHeight() const;

protected:
	LPDIRECT3DVERTEXBUFFER9 m_lpVertexBuffer;
	LPDIRECT3DINDEXBUFFER9 m_lpIndexBuffer;
	LPDIRECT3DTEXTURE9 m_lpTexture;

	D3DXMATRIX m_matPosition;
	int m_nWidth;
	int m_nHeight;
};

inline void cSprite::SetPosition( const D3DXVECTOR2 &position ) { D3DXMatrixTranslation( &m_matPosition, position.x, position.y, 0 ); }
inline void cSprite::SetWidth( const int &width )
{
	m_nWidth = width;

	SafeRelease( m_lpVertexBuffer );

	VERTEX2 v[] = {
		VERTEX2( 0.f, 0.f, 0.f, 0.f ),
		VERTEX2( static_cast< float >( m_nWidth ), 0.f, 1.f, 0.f ),
		VERTEX2( static_cast< float >( m_nWidth ), static_cast< float >( m_nHeight ), 1.f, 1.f ),
		VERTEX2( 0.f, static_cast< float >( m_nHeight ), 0.f, 1.f )
	};

	g_pEngine->core->lpd3dd9->CreateVertexBuffer( sizeof( v ), NULL, VERTEX2::FVF, D3DPOOL_DEFAULT, &m_lpVertexBuffer, nullptr );
	VERTEX2 *pVD;
	m_lpVertexBuffer->Lock( NULL, NULL, reinterpret_cast< void** >( &pVD ), NULL );
	memcpy( pVD, v, sizeof( v ) );
	m_lpVertexBuffer->Unlock();
}
inline void cSprite::SetHeight( const int &height )
{
	m_nHeight = height;

	SafeRelease( m_lpVertexBuffer );

	VERTEX2 v[] = {
		VERTEX2( 0.f, 0.f, 0.f, 0.f ),
		VERTEX2( static_cast< float >( m_nWidth ), 0.f, 1.f, 0.f ),
		VERTEX2( static_cast< float >( m_nWidth ), static_cast< float >( m_nHeight ), 1.f, 1.f ),
		VERTEX2( 0.f, static_cast< float >( m_nHeight ), 0.f, 1.f )
	};

	g_pEngine->core->lpd3dd9->CreateVertexBuffer( sizeof( v ), NULL, VERTEX2::FVF, D3DPOOL_DEFAULT, &m_lpVertexBuffer, NULL );
	VERTEX2 *pVD;
	m_lpVertexBuffer->Lock( NULL, NULL, reinterpret_cast< void** >( &pVD ), NULL );
	memcpy( pVD, v, sizeof( v ) );
	m_lpVertexBuffer->Unlock();
}
inline void cSprite::SetTexture( const LPDIRECT3DTEXTURE9 &texture ) { m_lpTexture = texture; }

inline D3DXVECTOR2 cSprite::GetPosition() const { return D3DXVECTOR2( m_matPosition( 3, 0 ), m_matPosition( 3, 1 ) ); }
inline const int& cSprite::GetWidth() const { return m_nWidth; }
inline const int& cSprite::GetHeight() const { return m_nHeight; }