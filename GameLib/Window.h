#pragma once
#include "Headers.h"

namespace lib
{
	class Window
	{
	public:
		Window();

		static HRESULT Init( int x, int y, int width, int height, const std::string& caption );
		static LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );

		static HWND get_hwnd();
		static int get_x();
		static int get_y();
		static int get_width();
		static int get_height();

	private:
		static WNDCLASSEX _wndClass;
		static HWND _hwnd;

		static int _x, _y;
		static int _width, _height;
		static std::string _caption;
		static bool _isFocus;
	};
}