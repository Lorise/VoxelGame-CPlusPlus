#pragma once
#include "Headers.h"

namespace lib
{
	class i_input_keyboard
	{
	public:
		enum KEYBOARD_KEY_STATE
		{
			KEYBOARD_KEY_UP,
			KEYBOARD_KEY_DOWN,
			KEYBOARD_KEY_PRESSED
		};

		i_input_keyboard();
		~i_input_keyboard();;

		KEYBOARD_KEY_STATE* GetKeysState();
		KEYBOARD_KEY_STATE GetKeyState( BYTE key );

		bool isKeyDown( BYTE key );
		bool isKeyUp( BYTE key );
		bool isKeyPress( BYTE key );

	protected:
		LPDIRECTINPUTDEVICE8 _keyboardDevice;
		KEYBOARD_KEY_STATE _keyboardData[ 256 ];
	};
}