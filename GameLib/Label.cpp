#include "Label.h"
#include "../VoxelGame/GameEngine.h"

namespace lib
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

		D3DXCreateFontIndirect( g_engine->core->d3dd9, &desk, &_font );
	}

	Label::~Label()
	{
		SafeRelease( _font );
	}

	void Label::Draw( const std::string string, const Rect< int> rect, const DWORD format ) const
	{
		RECT rectangle;

		rectangle.left = rect.x;
		rectangle.top = rect.y;
		rectangle.right = rect.x + rect.width;
		rectangle.bottom = rect.y + rect.height;

		_font->DrawTextA( nullptr, string.c_str(), -1, &rectangle, format, D3DCOLOR_XRGB( 255, 255, 255 ) );
	}
}
