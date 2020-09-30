#include "Input.h"
#include "../VoxelGame/BaseGenerator.h"

namespace lib
{
	input::input()
	{
		_directInput = nullptr;
	}

	input::~input()
	{
		SafeRelease( _directInput );
	}

	HRESULT input::Init( HWND hwnd )
	{
		HRESULT hr;

		hr = DirectInput8Create( GetModuleHandle( nullptr ), DIRECTINPUT_VERSION, IID_IDirectInput8, reinterpret_cast< void** >( &_directInput ), nullptr );
		if ( FAILED( hr ) )
		{
			MessageBoxA( nullptr, "DirectInput8Create", "Error", MB_OK | MB_ICONERROR );
			return E_FAIL;
		}

		hr = _directInput->CreateDevice( GUID_SysMouse, &_mouseDevice, nullptr );
		if ( FAILED( hr ) )
		{
			MessageBoxA( nullptr, "m_lpDirectInput->CreateDevice", "Error", MB_OK | MB_ICONERROR );
			return E_FAIL;
		}
		hr = _directInput->CreateDevice( GUID_SysKeyboard, &_keyboardDevice, nullptr );
		if ( FAILED( hr ) )
		{
			MessageBoxA( nullptr, "m_lpDirectInput->CreateDevice", "Error", MB_OK | MB_ICONERROR );
			return E_FAIL;
		}

		hr = _mouseDevice->SetDataFormat( &c_dfDIMouse );
		if ( FAILED( hr ) )
		{
			MessageBoxA( nullptr, "m_lpMouseDevice->SetDataFormat", "Error", MB_OK | MB_ICONERROR );
			return E_FAIL;
		}
		hr = _mouseDevice->SetCooperativeLevel( hwnd, DISCL_EXCLUSIVE | DISCL_NOWINKEY | DISCL_FOREGROUND );
		if ( FAILED( hr ) )
		{
			MessageBoxA( nullptr, "m_lpMouseDevice->SetCooperativeLevel", "Error", MB_OK | MB_ICONERROR );
			return E_FAIL;
		}

		hr = _keyboardDevice->SetDataFormat( &c_dfDIKeyboard );
		if ( FAILED( hr ) )
		{
			MessageBoxA( nullptr, "m_lpKeyboardDevice->SetDataFormat", "Error", MB_OK | MB_ICONERROR );
			return E_FAIL;
		}
		hr = _keyboardDevice->SetCooperativeLevel( hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE );
		if ( FAILED( hr ) )
		{
			MessageBoxA( nullptr, "m_lpKeyboardDevice->SetCooperativeLevel", "Error", MB_OK | MB_ICONERROR );
			return E_FAIL;
		}

		_mouseData.position = D3DXVECTOR2( 0, 0 );

		return D3D_OK;
	}

	void input::Grab()
	{
		MouseGrab();
		KeyboardGrab();
	}

	void input::MouseGrab()
	{
		HRESULT hr;

		hr = _mouseDevice->Acquire();
		if ( FAILED( hr ) )
		{
			_mouseData.changePosition = D3DXVECTOR2( 0, 0 );
			_mouseData.leftButtonState = MOUSE_STATE_UP;
			_mouseData.rightButtonState = MOUSE_STATE_DOWN;
			return;
		}

		DIMOUSESTATE mouseData;
		_mouseDevice->GetDeviceState( sizeof( DIMOUSESTATE ), &mouseData );

		_mouseData.position.x += static_cast< float >( mouseData.lX );
		_mouseData.position.y += static_cast< float >( mouseData.lY );
		if ( _mouseData.position.x < 0 )
			_mouseData.position.x = 0;
		if ( _mouseData.position.y < 0 )
			_mouseData.position.y = 0;
		_mouseData.changePosition = D3DXVECTOR2( static_cast< float >( mouseData.lX ), static_cast< float >( mouseData.lY ) );

		MOUSE_KEY_STATE state;

		if ( mouseData.rgbButtons[ 0 ] )
			state = MOUSE_STATE_DOWN;
		else
			state = MOUSE_STATE_UP;

		if ( _mouseData.leftButtonState == MOUSE_STATE_DOWN && state == MOUSE_STATE_UP )
			state = MOUSE_STATE_CLICK;

		_mouseData.leftButtonState = state;

		if ( mouseData.rgbButtons[ 1 ] )
			state = MOUSE_STATE_DOWN;
		else
			state = MOUSE_STATE_UP;

		if ( _mouseData.rightButtonState == MOUSE_STATE_DOWN && state == MOUSE_STATE_UP )
			state = MOUSE_STATE_CLICK;

		_mouseData.rightButtonState = state;
	}

	void input::KeyboardGrab()
	{
		HRESULT hr;

		hr = _keyboardDevice->Acquire();
		if ( FAILED( hr ) )
			return;

		BYTE keyboardData[ 256 ];
		_keyboardDevice->GetDeviceState( sizeof( keyboardData ), static_cast< LPVOID >( &keyboardData ) );

		KEYBOARD_KEY_STATE keyboardKeyState;

		for ( int i = 0; i < 256; i++ )
		{
			if ( keyboardData[ i ] )
				keyboardKeyState = KEYBOARD_KEY_DOWN;
			else
				keyboardKeyState = KEYBOARD_KEY_UP;

			if ( _keyboardData[ i ] == KEYBOARD_KEY_DOWN && keyboardKeyState == KEYBOARD_KEY_UP )
				keyboardKeyState = KEYBOARD_KEY_PRESSED;

			_keyboardData[ i ] = keyboardKeyState;
		}
	}
}
