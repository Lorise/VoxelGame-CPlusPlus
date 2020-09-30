#include "stdafx.h"
#include "HealthBar.h"
#include "Resource.h"

HealthBar::HealthBar()
{
	LPDIRECT3DTEXTURE9 texture = Resource::GetGuiTexture( "health.png" );
	m_realSizeTextureHealth = Resource::GetGuiTextureSize( "health.png" );

	m_autoPtrSpriteHealth = std::make_shared< cSprite >( D3DXVECTOR2( ( cWindow::GetWidth() - 810 ) / 2, cWindow::GetHeight() ),
														 m_realSizeTextureHealth.x, m_realSizeTextureHealth.y, texture );

	m_health = 0;
}

void HealthBar::Render()
{
	D3DXMATRIX translate;
	for( int i = 0; i < m_health; i++ )
	{
		D3DXMatrixTranslation( &translate, float( i * m_realSizeTextureHealth.x ), 0.f, 0.f );
		g_pEngine->core->lpd3dd9->SetTransform( D3DTS_WORLD, &translate );
		m_autoPtrSpriteHealth->Render();
	}
}

void HealthBar::Update()
{
	m_autoPtrSpriteHealth->SetPosition( D3DXVECTOR2( ( cWindow::GetWidth() - 810 ) / 2, cWindow::GetHeight() - 90 - m_realSizeTextureHealth.y ) );
}