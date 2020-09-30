#pragma once
#include "Headers.h"
#include "Sprite.h"
#include "Label.h"

namespace lib
{
	class Button
	{
	public:
		Button(D3DXVECTOR2 position, std::string label );
		~Button();

		void Render() const;
		void Update();

		void operator+=( void( *func )( ) );

		std::string GetLabel() const;
		bool isActive() const;
		bool isFocus() const;

		void SetActive(bool isActive );
		void SetLabel(std::string label );
		void SetTexture(LPDIRECT3DTEXTURE9 texture );
		void SetPosition(D3DXVECTOR2 position ) const;

	private:
		std::vector< void( *)( ) > _callbacks;
		LPDIRECT3DTEXTURE9 _texture;

		std::string _strLabel;
		Sprite* _sprite;
		Label* _label;

		bool _isActive;
		bool _isFocus;
	};
}