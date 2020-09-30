#include "iInputMouse.h"
#include "../VoxelGame/BaseGenerator.h"

namespace lib
{
	i_input_mouse::i_input_mouse()
	{
		_mouseDevice = nullptr;
	}

	i_input_mouse::~i_input_mouse()
	{
		SafeRelease( _mouseDevice );
	}

	i_input_mouse::MouseData i_input_mouse::GetMouseData() const
	{
		return _mouseData;
	}

	D3DXVECTOR2 i_input_mouse::GetChangeMousePos() const
	{
		return _mouseData.changePosition;
	};
	D3DXVECTOR2 i_input_mouse::GetPosition() const
	{
		return _mouseData.position;
	};

	i_input_mouse::MOUSE_KEY_STATE i_input_mouse::GetLeftButtonState() const
	{
		return _mouseData.leftButtonState;
	};
	i_input_mouse::MOUSE_KEY_STATE i_input_mouse::GetRightButtonState() const
	{
		return _mouseData.rightButtonState;
	}

	bool i_input_mouse::is_lkm_down() const
	{
		return _mouseData.leftButtonState == MOUSE_STATE_DOWN;
	}
	bool i_input_mouse::isLKMUP() const
	{
		return _mouseData.leftButtonState == MOUSE_STATE_UP;
	}
	bool i_input_mouse::isLKMClick() const
	{
		return _mouseData.leftButtonState == MOUSE_STATE_CLICK;
	}

	bool i_input_mouse::isRKMDown() const
	{
		return _mouseData.rightButtonState == MOUSE_STATE_DOWN;
	}
	bool i_input_mouse::isRKMUP() const
	{
		return _mouseData.rightButtonState == MOUSE_STATE_UP;
	}
	bool i_input_mouse::isRKMClick() const
	{
		return _mouseData.rightButtonState == MOUSE_STATE_CLICK;
	}
}
