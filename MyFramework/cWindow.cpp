#include "stdafx.h"
#include "cWindow.h"

WNDCLASSEX cWindow::m_wndClass;
HWND cWindow::m_hWnd;

int cWindow::m_nX, cWindow::m_nY;
int cWindow::m_nWidth, cWindow::m_nHeight;
std::string cWindow::m_strCaption;
bool cWindow::m_bFocus;

cWindow::cWindow()
{
	ZeroMemory( &m_wndClass, sizeof( WNDCLASSEX ) );
	m_hWnd = nullptr;

	m_nX = m_nY = 0;
	m_nWidth = 640;
	m_nHeight = 480;
	m_strCaption = "Main window";
	m_bFocus = true;
}

HRESULT cWindow::Init( int x = m_nX, int y = m_nY, int nWidth = m_nWidth, int nHeight = m_nHeight, std::string caption = m_strCaption )
{
	m_nX = x;
	m_nY = y;
	m_nWidth = nWidth;
	m_nHeight = nHeight;
	m_strCaption = caption;

	//wc.cbClsExtra = ?;
	m_wndClass.cbSize = sizeof( m_wndClass );
	//wc.cbWndExtra = ?;
	m_wndClass.hbrBackground = static_cast< HBRUSH >( GetStockObject( BLACK_BRUSH ) );
	m_wndClass.hCursor = LoadCursor( nullptr, IDC_ARROW );
	m_wndClass.hIcon = LoadIcon( nullptr, IDI_APPLICATION );
	m_wndClass.hIconSm = LoadIcon( nullptr, IDI_APPLICATION );
	m_wndClass.hInstance = GetModuleHandle( nullptr );
	m_wndClass.lpfnWndProc = WndProc;
	m_wndClass.lpszClassName = "Main";
	//wc.lpszMenuName = ?;
	m_wndClass.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;

	if( !RegisterClassEx( &m_wndClass ) )
	{
		MessageBox( nullptr, "Error RegisterClassEx", "Error", MB_OK | MB_ICONERROR );
		return E_FAIL;
	}

	m_hWnd = CreateWindow( m_wndClass.lpszClassName, caption.c_str(), WS_OVERLAPPEDWINDOW, x, y, nWidth, nHeight, NULL, NULL, m_wndClass.hInstance, NULL );
	if( !m_hWnd )
	{
		MessageBox( nullptr, "Error CreateWindow", "Error", MB_OK | MB_ICONERROR );
		return E_FAIL;
	}

	ShowWindow( m_hWnd, SW_SHOWDEFAULT );
	if( !UpdateWindow( m_hWnd ) )
	{
		MessageBox( nullptr, "Error UpdateWindow", "Error", MB_OK | MB_ICONERROR );
		return E_FAIL;
	}

	return S_OK;
}

LRESULT CALLBACK cWindow::WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch( uMsg )
	{
		case WM_SETFOCUS: m_bFocus = true; break;
		case WM_KILLFOCUS: m_bFocus = false; break;

		case WM_MOVE:
			m_nX = LOWORD( lParam );
			m_nY = HIWORD( lParam );
			break;

		case WM_SIZE:
			m_nWidth = LOWORD( lParam );
			m_nHeight = HIWORD( lParam );

			//g_pEngine->core->camera->SetAspect( m_nWidth / static_cast< float >( m_nHeight ) );
			break;

		case WM_DESTROY: PostQuitMessage( 0 ); break;
	}

	return DefWindowProc( hWnd, uMsg, wParam, lParam );
}