#include "Window.h"

namespace lib
{
	WNDCLASSEX Window::_wndClass;
	HWND Window::_hwnd;

	int Window::_x, Window::_y;
	int Window::_width, Window::_height;
	std::string Window::_caption;
	bool Window::_isFocus;

	Window::Window()
	{
		ZeroMemory( &_wndClass, sizeof( WNDCLASSEX ) );
		_hwnd = nullptr;

		_x = _y = 0;
		_width = 640;
		_height = 480;
		_caption = "Main window";
		_isFocus = true;
	}

	HRESULT Window::Init(const int x = _x, int y = _y, const int width = _width, const int height = _height, const std::string& caption = _caption )
	{
		_x = x;
		_y = y;
		_width = width;
		_height = height;
		_caption = caption;

		//wc.cbClsExtra = ?;
		_wndClass.cbSize = sizeof( _wndClass );
		//wc.cbWndExtra = ?;
		_wndClass.hbrBackground = static_cast< HBRUSH >( GetStockObject( BLACK_BRUSH ) );
		_wndClass.hCursor = LoadCursor( nullptr, IDC_ARROW );
		_wndClass.hIcon = LoadIcon( nullptr, IDI_APPLICATION );
		_wndClass.hIconSm = LoadIcon( nullptr, IDI_APPLICATION );
		_wndClass.hInstance = GetModuleHandle( nullptr );
		_wndClass.lpfnWndProc = WndProc;
		_wndClass.lpszClassName = "Main";
		//wc.lpszMenuName = ?;
		_wndClass.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;

		if ( !RegisterClassEx( &_wndClass ) )
		{
			MessageBox( nullptr, "Error RegisterClassEx", "Error", MB_OK | MB_ICONERROR );
			return E_FAIL;
		}

		_hwnd = CreateWindow( _wndClass.lpszClassName, caption.c_str(), WS_OVERLAPPEDWINDOW, x, y, width, height, NULL, NULL, _wndClass.hInstance, NULL );
		if ( !_hwnd )
		{
			MessageBox( nullptr, "Error CreateWindow", "Error", MB_OK | MB_ICONERROR );
			return E_FAIL;
		}

		ShowWindow( _hwnd, SW_SHOWDEFAULT );
		if ( !UpdateWindow( _hwnd ) )
		{
			MessageBox( nullptr, "Error UpdateWindow", "Error", MB_OK | MB_ICONERROR );
			return E_FAIL;
		}

		return S_OK;
	}

	LRESULT CALLBACK Window::WndProc(const HWND hwnd, const UINT msg, const WPARAM w_param, const LPARAM l_param )
	{
		switch ( msg )
		{
			case WM_SETFOCUS: _isFocus = true; break;
			case WM_KILLFOCUS: _isFocus = false; break;

			case WM_MOVE:
				_x = LOWORD( l_param );
				_y = HIWORD( l_param );
				break;

			case WM_SIZE:
				_width = LOWORD( l_param );
				_height = HIWORD( l_param );
				break;

			case WM_DESTROY: PostQuitMessage( 0 ); break;
		}

		return DefWindowProc( hwnd, msg, w_param, l_param );
	}

	HWND Window::get_hwnd()
	{
		return _hwnd;
	}
	int Window::get_x()
	{
		return _x;
	}
	int Window::get_y()
	{
		return _y;
	}
	int Window::get_width()
	{
		return _width;
	}
	int Window::get_height()
	{
		return _height;
	}
}