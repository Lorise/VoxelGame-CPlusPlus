#pragma once
#include "Headers.h"

namespace lib
{
	class Sprite
	{
	public:
		Sprite(D3DXVECTOR2 position, int width, int height, LPDIRECT3DTEXTURE9 texture );
		~Sprite();

		virtual void Render();

		void SetPosition(D3DXVECTOR2 position );
		void SetWidth(int width );
		void SetHeight(int height );
		void SetTexture( LPDIRECT3DTEXTURE9 texture );

		D3DXVECTOR2 GetPosition() const;
		int GetWidth() const;
		int GetHeight() const;

	protected:
		LPDIRECT3DVERTEXBUFFER9 _vertexBuffer;
		LPDIRECT3DINDEXBUFFER9 _indexBuffer;
		LPDIRECT3DTEXTURE9 _texture;

		D3DXMATRIX _position;
		int _width;
		int _height;
	};
}