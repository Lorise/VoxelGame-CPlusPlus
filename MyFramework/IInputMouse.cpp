#include "stdafx.h"
#include "IInputMouse.h"
#include "functional.h"

namespace mf
{
	IInputMouse::IInputMouse()
	{
		m_lpMouseDevice = nullptr;
	}

	IInputMouse::~IInputMouse()
	{
		SafeRelease( m_lpMouseDevice );
	}
}