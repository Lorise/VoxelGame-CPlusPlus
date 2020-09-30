#pragma once
#include "Headers.h"
#include "Sprite.h"

namespace lib
{
	class Background
	{
	public:
		Background(LPDIRECT3DTEXTURE9 texture );
		~Background();

		void Render() const;
		void Update() const;

		void SetTexture(LPDIRECT3DTEXTURE9 texture ) const;

	private:
		Sprite* _sprite;
	};
}