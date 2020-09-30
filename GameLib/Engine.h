#pragma once
#include "Core.h"
#include "InputSystem.h"
#include "SoundSystem.h"

namespace lib
{
	class core;
	class input_system;
	class sound_system;

	class engine
	{
	public:
		engine();
		~engine();

		core* core;
		input_system* input;
		sound_system* sound;
	};
}