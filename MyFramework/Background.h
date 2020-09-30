#pragma once
#include "Sprite.h"

namespace mf
{
	namespace ui
	{
		class Background
		{
		public:
			Background() = delete;
			Background( const LPDIRECT3DTEXTURE9 &texture );
			~Background();

			void Render();
			void Update();

			void SetTexture( const LPDIRECT3DTEXTURE9 &texture );

		private:
			cSprite *m_spriteBackground;
		};

		inline void Background::SetTexture( const LPDIRECT3DTEXTURE9 &texture ) { m_spriteBackground->SetTexture( texture ); }
	}
}