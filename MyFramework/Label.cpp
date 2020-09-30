#include "stdafx.h"
#include "Label.h"
#include "EnginePointers.h"

namespace mf
{
	namespace ui
	{
		Label::Label()
		{
			D3DXFONT_DESCA desk = { 0 };
			desk.CharSet = DEFAULT_CHARSET;
			strcpy_s( desk.FaceName, "Times New Roman" );
			desk.Height = 30;
			desk.Width = 15;
			desk.Weight = FW_NORMAL;
			desk.Italic = false;

			D3DXCreateFontIndirect( g_pEngine->core->lpd3dd9, &desk, &m_font );
		}

		Label::~Label()
		{
			SafeRelease( m_font );
		}

		void Label::Draw( const std::string &string, const RECT< int> &rect, const DWORD &format )
		{
			::RECT rectangle;
			rectangle.left = rect.x;
			rectangle.top = rect.y;
			rectangle.right = rect.x + rect.width;
			rectangle.bottom = rect.y + rect.height;
			m_font->DrawTextA(nullptr, string.c_str(), -1, &rectangle, format, D3DCOLOR_XRGB( 255, 255, 255 ) );
		}
	}
}