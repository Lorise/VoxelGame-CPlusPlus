#pragma once

namespace mf
{
	class IInputMouse
	{
	public:
		enum EMouseButtonState { Button_up, Button_down, Button_click };
		struct MouseData
		{
			D3DXVECTOR2 position;
			D3DXVECTOR2 changePosition;
			EMouseButtonState leftButtonState;
			EMouseButtonState rightButtonState;
		};

		IInputMouse();
		~IInputMouse();

		MouseData GetMouseData();

		D3DXVECTOR2 GetChangeMousePos();
		D3DXVECTOR2 GetPosition();

		EMouseButtonState GetLeftButtonState();
		EMouseButtonState GetRightButtonState();

		bool isLKMDown();
		bool isLKMUP();
		bool isLKMClick();

		bool isRKMDown();
		bool isRKMUP();
		bool isRKMClick();

	protected:
		LPDIRECTINPUTDEVICE8 m_lpMouseDevice;
		MouseData m_mouseData;
	};

	inline IInputMouse::MouseData IInputMouse::GetMouseData() { return m_mouseData; }

	inline D3DXVECTOR2 IInputMouse::GetChangeMousePos() { return m_mouseData.changePosition; };
	inline D3DXVECTOR2 IInputMouse::GetPosition() { return m_mouseData.position; };

	inline IInputMouse::EMouseButtonState IInputMouse::GetLeftButtonState() { return m_mouseData.leftButtonState; };
	inline IInputMouse::EMouseButtonState IInputMouse::GetRightButtonState() { return m_mouseData.rightButtonState; }

	inline bool IInputMouse::isLKMDown() { return m_mouseData.leftButtonState == Button_down ? true : false; }
	inline bool IInputMouse::isLKMUP() { return m_mouseData.leftButtonState == Button_up ? true : false; }
	inline bool IInputMouse::isLKMClick() { return m_mouseData.leftButtonState == Button_click ? true : false; }

	inline bool IInputMouse::isRKMDown() { return m_mouseData.rightButtonState == Button_down ? true : false; }
	inline bool IInputMouse::isRKMUP() { return  m_mouseData.rightButtonState == Button_up ? true : false; }
	inline bool IInputMouse::isRKMClick() { return m_mouseData.rightButtonState == Button_click ? true : false; }
}