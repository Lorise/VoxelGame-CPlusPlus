#pragma once
#include "functional.h"

namespace mf
{
	namespace ui
	{
		class Label
		{
		public:
			Label();
			~Label();

			void Draw( const std::string &string, const RECT< int> &rect, const DWORD &format );

		private:
			LPD3DXFONT m_font;
		};
	}
}