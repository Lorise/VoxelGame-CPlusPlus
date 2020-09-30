#include "stdafx.h"
#include "Button.h"
#include "functional.h"
#include "EnginePointers.h"
#include "Sprite.h"
#include "Label.h"
#include "IInputMouse.h"

namespace mf
{
	namespace ui
	{
		Button::Button( const D3DXVECTOR2 &position, const std::string &label )
		{
			m_texButton = nullptr;

			m_strLabel = label;
			m_spriteButton = new cSprite( position, 792, 64, m_texButton );
			m_label = new Label();

			m_bActive = true;
			m_bFocus = false;
		}

		Button::~Button()
		{
			SafeDeletePtr( m_spriteButton );
			SafeDeletePtr( m_label );
		}

		void Button::Render()
		{
			D3DXMATRIX world;
			D3DXMatrixIdentity( &world );
			g_pEngine->core->lpd3dd9->SetTransform( D3DTS_WORLD, &world );
			m_spriteButton->SetTexture( m_texButton );
			m_spriteButton->Render();

			m_label->Draw( m_strLabel, RECT< int >(
				static_cast< int >( m_spriteButton->GetPosition().x ),
				static_cast< int >( m_spriteButton->GetPosition().y ),
				static_cast< int >( m_spriteButton->GetWidth() ),
				static_cast< int >( m_spriteButton->GetHeight() ) ), DT_CENTER | DT_VCENTER );
		}

		void Button::Update()
		{
			if( g_pEngine->input->mouse->GetPosition().x > m_spriteButton->GetPosition().x && g_pEngine->input->mouse->GetPosition().x < m_spriteButton->GetPosition().x + m_spriteButton->GetWidth() &&
				g_pEngine->input->mouse->GetPosition().y > m_spriteButton->GetPosition().y && g_pEngine->input->mouse->GetPosition().y < m_spriteButton->GetPosition().y + m_spriteButton->GetHeight() )
			{
				m_bFocus = true;

				if( g_pEngine->input->mouse->isLKMClick() )
					for( auto it : m_vCallback )
						it();
			}
			else
				m_bFocus = false;
		}
	}
}