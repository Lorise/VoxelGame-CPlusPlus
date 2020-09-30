#include "Engine.h"
#include "../VoxelGame/GameEngine.h"
#include "Core.h"

namespace lib
{
	engine::engine()
	{
		core = new lib::core();
		input = new input_system();
		sound = new sound_system();
	}

	engine::~engine()
	{
		SafeDeletePtr( core );
		SafeDeletePtr( input );
		SafeDeletePtr( sound );
	}
}
