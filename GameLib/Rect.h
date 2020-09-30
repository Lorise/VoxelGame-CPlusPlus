#pragma once

namespace lib
{
	template< class T >
	struct Rect
	{
		Rect()
		{
			x = 0;
			y = 0;
			width = 0;
			height = 0;
		}

		Rect( const T x, const T y, const T width, const T height )
		{
			this->x = x;
			this->y = y;

			this->width = width;
			this->height = height;
		}

		T x, y;
		T width, height;
	};
}