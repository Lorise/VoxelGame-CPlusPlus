#pragma once
#include "iInputMouse.h"
#include "iInputKeyboard.h"

namespace lib
{
	class input_system
	{
	public:
		i_input_mouse* mouse;
		i_input_keyboard* keyboard;
	};
}
