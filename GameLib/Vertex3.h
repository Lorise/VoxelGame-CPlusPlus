#pragma once
#include "Headers.h"

namespace lib
{
	struct Vertex3
	{
		Vertex3()
		{
		}
		Vertex3(
			const float x, const float y, const float z,
			const float nx, const float ny, const float nz,
			const float tx, const float ty )
		{
			this->position = D3DXVECTOR3( x, y, z );
			this->normal = D3DXVECTOR3( nx, ny, nz );
			this->tex = D3DXVECTOR2( tx, ty );
		}

		D3DXVECTOR3 position;
		D3DXVECTOR3 normal;
		D3DXVECTOR2 tex;
		static const DWORD FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;
	};
}