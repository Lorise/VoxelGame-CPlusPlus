#include "stdafx.h"
#include "Sprite.h"
#include "cCamera.h"

cSprite::cSprite( const D3DXVECTOR2 &position, const int &width, const int &height, const LPDIRECT3DTEXTURE9 &texture )
{
	D3DXMatrixTranslation( &m_matPosition, position.x, position.y, 0 );
	m_nWidth = width;
	m_nHeight = height;
	m_lpTexture = texture;

	VERTEX2 v[] = {
		VERTEX2( 0.f, 0.f, 0.f, 0.f ),
		VERTEX2( static_cast< float >( m_nWidth ), 0.f, 1.f, 0.f ),
		VERTEX2( static_cast< float >( m_nWidth ), static_cast< float >( m_nHeight ), 1.f, 1.f ),
		VERTEX2( 0.f, static_cast< float >( m_nHeight ), 0.f, 1.f )
	};

	g_pEngine->core->lpd3dd9->CreateVertexBuffer( sizeof( v )* sizeof( VERTEX2 ), NULL, VERTEX2::FVF, D3DPOOL_DEFAULT, &m_lpVertexBuffer, nullptr );
	VERTEX2 *pVD;
	m_lpVertexBuffer->Lock( NULL, NULL, reinterpret_cast< void** >( &pVD ), NULL );
	memcpy( pVD, v, sizeof( v ) );
	m_lpVertexBuffer->Unlock();

	WORD index[] = { 0, 1, 2, 2, 3, 0 };

	g_pEngine->core->lpd3dd9->CreateIndexBuffer( sizeof( index ), NULL, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_lpIndexBuffer, nullptr );
	WORD *pID;
	m_lpIndexBuffer->Lock( NULL, NULL, reinterpret_cast< void** >( &pID ), NULL );
	memcpy( pID, index, sizeof( index ) );
	m_lpIndexBuffer->Unlock();
}

cSprite::~cSprite()
{
	SafeRelease( m_lpVertexBuffer );
	SafeRelease( m_lpIndexBuffer );
}

void cSprite::Render()
{
	g_pEngine->core->camera->Begin2D();

	g_pEngine->core->lpd3dd9->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
	g_pEngine->core->lpd3dd9->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	g_pEngine->core->lpd3dd9->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
	g_pEngine->core->lpd3dd9->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );

	g_pEngine->core->lpd3dd9->SetFVF( VERTEX2::FVF );
	g_pEngine->core->lpd3dd9->SetStreamSource( NULL, m_lpVertexBuffer, NULL, sizeof( VERTEX2 ) );
	g_pEngine->core->lpd3dd9->SetIndices( m_lpIndexBuffer );
	g_pEngine->core->lpd3dd9->SetTexture( 0, m_lpTexture );

	D3DXMATRIX world;
	g_pEngine->core->lpd3dd9->GetTransform( D3DTS_WORLD, &world );
	g_pEngine->core->lpd3dd9->SetTransform( D3DTS_WORLD, &( m_matPosition * world ) );
	g_pEngine->core->lpd3dd9->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, NULL, NULL, 6, 0, 2 );

	g_pEngine->core->lpd3dd9->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE );

	g_pEngine->core->camera->End2D();
}