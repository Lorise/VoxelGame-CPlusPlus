#include "stdafx.h"
#include "SelectPanel.h"
#include "Resource.h"

SelectPanel::SelectPanel()
{
	LPDIRECT3DTEXTURE9 texture;

	texture = Resource::GetGuiTexture( "widget.png" );
	m_realTextureSizeSelectPanel = Resource::GetGuiTextureSize( "widget.png" );
	m_autoPtrSpriteSelectPanel = std::make_shared<cSprite>( D3DXVECTOR2( ( cWindow::GetWidth() - 810 ) / 2, cWindow::GetHeight() - m_realTextureSizeSelectPanel.y ),
															m_realTextureSizeSelectPanel.x, m_realTextureSizeSelectPanel.y, texture );

	texture = Resource::GetGuiTexture( "selectitem.png" );
	m_realTextureSizeSelectItem = Resource::GetGuiTextureSize( "selectitem.png" );
	m_autoPtrSpriteSelectItem = std::make_shared<cSprite>( m_autoPtrSpriteSelectPanel->GetPosition(),
														   m_realTextureSizeSelectItem.x, m_realTextureSizeSelectItem.y, texture );

	m_select = 0;
}

void SelectPanel::Render()
{
	D3DXMATRIX translate;
	D3DXMatrixIdentity( &translate );
	g_pEngine->core->lpd3dd9->SetTransform( D3DTS_WORLD, &translate );

	m_autoPtrSpriteSelectPanel->Render();

	D3DXMatrixTranslation( &translate, float( m_select * m_realTextureSizeSelectItem.x ), 0.f, 0.f );
	g_pEngine->core->lpd3dd9->SetTransform( D3DTS_WORLD, &translate );
	m_autoPtrSpriteSelectItem->Render();
}

void SelectPanel::Update()
{
	m_autoPtrSpriteSelectPanel->SetPosition( D3DXVECTOR2( ( cWindow::GetWidth() - 810 ) / 2, cWindow::GetHeight() - m_realTextureSizeSelectItem.y ) );
	m_autoPtrSpriteSelectItem->SetPosition( m_autoPtrSpriteSelectPanel->GetPosition() );
}

void SelectPanel::Event()
{
	if( g_pEngine->input->keyboard->isKeyPress( DIK_NUMPAD4 ) )
		m_select--;
	if( m_select < 0 )
		m_select = 8;

	if( g_pEngine->input->keyboard->isKeyPress( DIK_NUMPAD6 ) )
		m_select++;
	if( m_select > 8 )
		m_select = 0;
}