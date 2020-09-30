#pragma once
#include "Headers.h"

struct VERTEX2
{
	VERTEX2()
	{
	}
	VERTEX2( const float &x, const float &y, const float &tu, const float &tv )
	{
		this->position = D3DXVECTOR3( x, y, 0 );
		this->tex = D3DXVECTOR2( tu, tv );
	}

	D3DXVECTOR3 position;
	D3DXVECTOR2 tex;

	static const DWORD FVF = D3DFVF_XYZ | D3DFVF_TEX1;
};