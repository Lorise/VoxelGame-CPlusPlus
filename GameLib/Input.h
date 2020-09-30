#pragma once
#include "iInputMouse.h"
#include "iInputKeyboard.h"

namespace lib
{
	class input :
		public i_input_mouse,
		public i_input_keyboard
	{
	public:
		input();
		~input();

		HRESULT Init( HWND hwnd );
		void Grab();

	private:
		void MouseGrab();
		void KeyboardGrab();

	private:
		LPDIRECTINPUT8 _directInput;
	};
}