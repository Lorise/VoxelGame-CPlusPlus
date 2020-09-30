#include "Core.h"
#include "../VoxelGame/BaseGenerator.h"

namespace lib
{
	core::core()
	{
		d3d9 = nullptr;
		d3dd9 = nullptr;

		camera = nullptr;
	}

	core::~core()
	{
		SafeRelease( d3dd9 );
		SafeRelease( d3d9 );

		delete camera;
	}
}
