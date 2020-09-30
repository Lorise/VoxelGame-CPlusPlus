#include "stdafx.h"
#include "HungerBar.h"
#include "Resource.h"

HungerBar::HungerBar()
{
	LPDIRECT3DTEXTURE9 texture = Resource::GetGuiTexture( "hunger.png" );
	m_realTextureSizeHunger = Resource::GetGuiTextureSize( "hunger.png" );

	m_autoPtrSpriteHunger = std::make_shared< cSprite >( D3DXVECTOR2(
		( cWindow::GetWidth() + 810 ) / 2 - 10 * m_realTextureSizeHunger.x, cWindow::GetHeight() - 90 - m_realTextureSizeHunger.y ),
		m_realTextureSizeHunger.x, m_realTextureSizeHunger.y, texture );

	m_hunger = 0;
}

void HungerBar::Render()
{
	D3DXMATRIX translate;
	for( int i = 0; i < m_hunger; i++ )
	{
		D3DXMatrixTranslation( &translate, float( i * m_realTextureSizeHunger.x ), 0.f, 0.f );
		g_pEngine->core->lpd3dd9->SetTransform( D3DTS_WORLD, &translate );
		m_autoPtrSpriteHunger->Render();
	}
}

void HungerBar::Update()
{
	m_autoPtrSpriteHunger->SetPosition( D3DXVECTOR2( ( cWindow::GetWidth() + 810 ) / 2 - 10 * m_realTextureSizeHunger.x, cWindow::GetHeight() - 90 - m_realTextureSizeHunger.y ) );
}