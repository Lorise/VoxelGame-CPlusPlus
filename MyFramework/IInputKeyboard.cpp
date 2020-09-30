#include "stdafx.h"
#include "IInputKeyboard.h"
#include "functional.h"

namespace mf
{
	IInputKeyboard::IInputKeyboard()
	{
		m_lpKeyboardDevice = nullptr;
	}

	IInputKeyboard::~IInputKeyboard()
	{
		SafeRelease( m_lpKeyboardDevice );
	}
}