#pragma once

namespace mf
{
	class IInputKeyboard
	{
	public:
		enum EKeyboardKeyState { Key_up, Key_down, Key_pressed };

		IInputKeyboard();
		~IInputKeyboard();;

		EKeyboardKeyState* GetKeysState();
		EKeyboardKeyState GetKeyState( BYTE key );

		bool isKeyDown( BYTE key );
		bool isKeyUp( BYTE key );
		bool isKeyPress( BYTE key );

	protected:
		LPDIRECTINPUTDEVICE8 m_lpKeyboardDevice;
		EKeyboardKeyState m_keyboardData[ 256 ];
	};

	inline IInputKeyboard::EKeyboardKeyState* IInputKeyboard::GetKeysState() { return m_keyboardData; }
	inline IInputKeyboard::EKeyboardKeyState IInputKeyboard::GetKeyState( BYTE key ) { return m_keyboardData[ key ]; }

	inline bool IInputKeyboard::isKeyDown( BYTE key ) { return m_keyboardData[ key ] == Key_down ? true : false; }
	inline bool IInputKeyboard::isKeyUp( BYTE key ) { return m_keyboardData[ key ] == Key_up ? true : false; }
	inline bool IInputKeyboard::isKeyPress( BYTE key ) { return m_keyboardData[ key ] == Key_pressed ? true : false; }
}