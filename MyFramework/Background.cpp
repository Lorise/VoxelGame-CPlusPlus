#include "stdafx.h"
#include "Background.h"
#include "cWindow.h"
#include "functional.h"
#include "EnginePointers.h"
#include "Sprite.h"

namespace mf
{
	namespace ui
	{
		Background::Background( const LPDIRECT3DTEXTURE9 &texture )
		{
			m_spriteBackground = new cSprite( D3DXVECTOR2( 0, 0 ), cWindow::GetWidth(), cWindow::GetHeight(), texture );
		}

		Background::~Background()
		{
			SafeDeletePtr( m_spriteBackground );
		}

		void Background::Render()
		{
			D3DXMATRIX world;
			D3DXMatrixIdentity( &world );
			g_pEngine->core->lpd3dd9->SetTransform( D3DTS_WORLD, &world );

			m_spriteBackground->Render();
		}

		void Background::Update()
		{
			m_spriteBackground->SetWidth( cWindow::GetWidth() );
			m_spriteBackground->SetHeight( cWindow::GetHeight() );
		}
	}
}