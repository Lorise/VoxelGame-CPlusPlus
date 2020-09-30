#include "stdafx.h"
#include "Cursor.h"
#include "Resource.h"

Cursor::Cursor()
{
	LPDIRECT3DTEXTURE9 texture = Resource::GetGuiTexture( "cursor.png" );
	D3DXVECTOR2 sizeTextureCursor = Resource::GetGuiTextureSize( "cursor.png" );
	m_spriteCursor = std::make_shared< cSprite >( g_pEngine->input->mouse->GetPosition(), sizeTextureCursor.x, sizeTextureCursor.y, texture );
}

void Cursor::Render()
{
	D3DXMATRIX translate;
	D3DXMatrixIdentity( &translate );
	g_pEngine->core->lpd3dd9->SetTransform( D3DTS_WORLD, &translate );
	m_spriteCursor->Render();
}

void Cursor::Update()
{
	m_spriteCursor->SetPosition( g_pEngine->input->mouse->GetPosition() );
}