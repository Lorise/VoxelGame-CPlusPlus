#include "stdafx.h"
#include "Input.h"
#include "functional.h"

namespace mf
{
	Input::Input()
	{
		m_lpDirectInput = nullptr;
	}

	Input::~Input()
	{
		SafeRelease( m_lpDirectInput );
	}

	HRESULT Input::Init( HWND hWnd )
	{
		HRESULT hr;

		hr = DirectInput8Create( GetModuleHandle( nullptr ), DIRECTINPUT_VERSION, IID_IDirectInput8, reinterpret_cast< void** >( &m_lpDirectInput ), nullptr );
		if( FAILED( hr ) )
		{
			MessageBoxA( nullptr, "DirectInput8Create", "Error", MB_OK | MB_ICONERROR );
			return E_FAIL;
		}

		hr = m_lpDirectInput->CreateDevice( GUID_SysMouse, &m_lpMouseDevice, nullptr );
		if( FAILED( hr ) )
		{
			MessageBoxA( nullptr, "m_lpDirectInput->CreateDevice", "Error", MB_OK | MB_ICONERROR );
			return E_FAIL;
		}
		hr = m_lpDirectInput->CreateDevice( GUID_SysKeyboard, &m_lpKeyboardDevice, nullptr );
		if( FAILED( hr ) )
		{
			MessageBoxA( nullptr, "m_lpDirectInput->CreateDevice", "Error", MB_OK | MB_ICONERROR );
			return E_FAIL;
		}

		hr = m_lpMouseDevice->SetDataFormat( &c_dfDIMouse );
		if( FAILED( hr ) )
		{
			MessageBoxA( nullptr, "m_lpMouseDevice->SetDataFormat", "Error", MB_OK | MB_ICONERROR );
			return E_FAIL;
		}
		hr = m_lpMouseDevice->SetCooperativeLevel( hWnd, DISCL_EXCLUSIVE | DISCL_NOWINKEY | DISCL_FOREGROUND );
		if( FAILED( hr ) )
		{
			MessageBoxA( nullptr, "m_lpMouseDevice->SetCooperativeLevel", "Error", MB_OK | MB_ICONERROR );
			return E_FAIL;
		}

		hr = m_lpKeyboardDevice->SetDataFormat( &c_dfDIKeyboard );
		if( FAILED( hr ) )
		{
			MessageBoxA( nullptr, "m_lpKeyboardDevice->SetDataFormat", "Error", MB_OK | MB_ICONERROR );
			return E_FAIL;
		}
		hr = m_lpKeyboardDevice->SetCooperativeLevel( hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE );
		if( FAILED( hr ) )
		{
			MessageBoxA( nullptr, "m_lpKeyboardDevice->SetCooperativeLevel", "Error", MB_OK | MB_ICONERROR );
			return E_FAIL;
		}

		m_mouseData.position = D3DXVECTOR2( 0, 0 );

		return D3D_OK;
	}

	void Input::Grab()
	{
		HRESULT hr;

	#pragma region mouse
		hr = m_lpMouseDevice->Acquire();
		if( FAILED( hr ) )
		{
			m_mouseData.changePosition = D3DXVECTOR2( 0, 0 );
			m_mouseData.leftButtonState = Button_up;
			m_mouseData.rightButtonState = Button_down;
			return;
		}

		DIMOUSESTATE mouseData;
		m_lpMouseDevice->GetDeviceState( sizeof( DIMOUSESTATE ), &mouseData );

		m_mouseData.position.x += static_cast<float>(mouseData.lX);
		m_mouseData.position.y += static_cast<float>(mouseData.lY);
		if( m_mouseData.position.x < 0 )
			m_mouseData.position.x = 0;
		if( m_mouseData.position.y < 0 )
			m_mouseData.position.y = 0;
		m_mouseData.changePosition = D3DXVECTOR2(static_cast<float>(mouseData.lX), static_cast<float>(mouseData.lY) );

		EMouseButtonState state;

	#pragma region LB
		if( mouseData.rgbButtons[ 0 ] )
			state = Button_down;
		else
			state = Button_up;

		if( m_mouseData.leftButtonState == Button_down && state == Button_up )
			state = Button_click;

		m_mouseData.leftButtonState = state;
	#pragma endregion 

	#pragma region RB
		if( mouseData.rgbButtons[ 1 ] )
			state = Button_down;
		else
			state = Button_up;

		if( m_mouseData.rightButtonState == Button_down && state == Button_up )
			state = Button_click;

		m_mouseData.rightButtonState = state;
	#pragma endregion
	#pragma endregion 

	#pragma region keyboard
		hr = m_lpKeyboardDevice->Acquire();
		if( FAILED( hr ) ) return;

		BYTE keyboardData[ 256 ];
		m_lpKeyboardDevice->GetDeviceState( sizeof( keyboardData ), static_cast< LPVOID >( &keyboardData ) );

		EKeyboardKeyState keyboardKeyState;

		for( int i = 0; i < 256; i++ )
		{
			if( keyboardData[ i ] )
				keyboardKeyState = Key_down;
			else
				keyboardKeyState = Key_up;

			if( m_keyboardData[ i ] == Key_down && keyboardKeyState == Key_up )
				keyboardKeyState = Key_pressed;

			m_keyboardData[ i ] = keyboardKeyState;
		}
	#pragma endregion
	}
}