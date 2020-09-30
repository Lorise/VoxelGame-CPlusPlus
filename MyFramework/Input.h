#pragma once
#include "IInputMouse.h"
#include "IInputKeyboard.h"

namespace mf
{
	class Input:
		public IInputMouse,
		public IInputKeyboard
	{
	public:
		Input();
		~Input();

		HRESULT Init( HWND hWnd );
		void Grab();

	private:
		LPDIRECTINPUT8 m_lpDirectInput;
	};
}