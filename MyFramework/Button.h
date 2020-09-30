#pragma once
#include "Sprite.h"

namespace mf
{
	namespace ui
	{
		class Label;
	}
}


namespace mf
{
	namespace ui
	{
		class Button
		{
		public:
			Button() = delete;
			Button( const D3DXVECTOR2 &position, const std::string &label );
			~Button();

			void Render();
			void Update();

			void operator+=( void( *func )( ) );

			std::string GetLabel() const;
			const bool& isActive() const;
			const bool& isFocus() const;

			void SetActive( const bool &active );
			void SetLabel( const std::string &label );
			void SetTexture( const LPDIRECT3DTEXTURE9 &texture );
			void SetPosition( const D3DXVECTOR2 &position );

		private:
			std::vector< void( *)( ) > m_vCallback;
			LPDIRECT3DTEXTURE9 m_texButton;

			std::string m_strLabel;
			cSprite *m_spriteButton;
			Label *m_label;

			bool m_bActive;
			bool m_bFocus;
		};

		inline void Button::operator+=( void( *func )( ) ) { m_vCallback.push_back( func ); }

		inline std::string Button::GetLabel() const { return m_strLabel; }
		inline const bool& Button::isActive() const { return m_bActive; }
		inline const bool& Button::isFocus() const { return m_bFocus; }

		inline void Button::SetActive( const bool &active ) { m_bActive = active; }
		inline void Button::SetLabel( const std::string &label ) { m_strLabel = label; }
		inline void Button::SetTexture( const LPDIRECT3DTEXTURE9 &texture ) { m_texButton = texture; }
		inline void Button::SetPosition( const D3DXVECTOR2 &position ) { m_spriteButton->SetPosition( position ); }
	}
}