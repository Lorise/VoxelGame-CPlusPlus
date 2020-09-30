#include "iInputKeyboard.h"
#include "../VoxelGame/BaseGenerator.h"

namespace lib
{
	i_input_keyboard::i_input_keyboard()
	{
		_keyboardDevice = nullptr;
	}

	i_input_keyboard::~i_input_keyboard()
	{
		SafeRelease( _keyboardDevice );
	}

	i_input_keyboard::KEYBOARD_KEY_STATE* i_input_keyboard::GetKeysState()
	{
		return _keyboardData;
	}
	i_input_keyboard::KEYBOARD_KEY_STATE i_input_keyboard::GetKeyState( BYTE key )
	{
		return _keyboardData[ key ];
	}

	bool i_input_keyboard::isKeyDown( BYTE key )
	{
		return _keyboardData[ key ] == KEYBOARD_KEY_DOWN ? true : false;
	}
	bool i_input_keyboard::isKeyUp( BYTE key )
	{
		return _keyboardData[ key ] == KEYBOARD_KEY_UP ? true : false;
	}
	bool i_input_keyboard::isKeyPress( BYTE key )
	{
		return _keyboardData[ key ] == KEYBOARD_KEY_PRESSED ? true : false;
	}
}
