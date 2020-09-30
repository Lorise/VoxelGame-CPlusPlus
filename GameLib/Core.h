#pragma once
#include "Headers.h"
#include "Camera.h"

namespace lib
{
	class camera;

	class core
	{
	public:
		core();
		~core();

		LPDIRECT3D9 d3d9;
		LPDIRECT3DDEVICE9 d3dd9;

		camera* camera;
	};
}