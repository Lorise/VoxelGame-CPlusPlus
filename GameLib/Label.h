#pragma once
#include "Headers.h"
#include "Rect.h"

namespace lib
{
	class Label
	{
	public:
		Label();
		~Label();

		void Draw(std::string string, Rect< int> rect, DWORD format ) const;

	private:
		LPD3DXFONT _font;
	};
}