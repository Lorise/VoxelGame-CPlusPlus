#pragma once
#include "Headers.h"

namespace lib
{
	class i_input_mouse
	{
	public:
		enum MOUSE_KEY_STATE
		{
			MOUSE_STATE_UP,
			MOUSE_STATE_DOWN,
			MOUSE_STATE_CLICK
		};

		struct MouseData
		{
			D3DXVECTOR2 position;
			D3DXVECTOR2 changePosition;
			MOUSE_KEY_STATE leftButtonState;
			MOUSE_KEY_STATE rightButtonState;
		};

		i_input_mouse();
		~i_input_mouse();

		MouseData GetMouseData() const;

		D3DXVECTOR2 GetChangeMousePos() const;
		D3DXVECTOR2 GetPosition() const;

		MOUSE_KEY_STATE GetLeftButtonState() const;
		MOUSE_KEY_STATE GetRightButtonState() const;

		bool is_lkm_down() const;
		bool isLKMUP() const;
		bool isLKMClick() const;

		bool isRKMDown() const;
		bool isRKMUP() const;
		bool isRKMClick() const;

	protected:
		LPDIRECTINPUTDEVICE8 _mouseDevice;
		MouseData _mouseData;
	};
}