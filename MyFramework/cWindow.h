#pragma once

class cWindow
{
public:
	cWindow();
	static HRESULT Init( int x, int y, int nWidth, int nHeight, std::string caption );
	static LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

	static HWND GetHwnd();
	static int GetX();
	static int GetY();
	static int GetWidth();
	static int GetHeight();

private:
	static WNDCLASSEX m_wndClass;
	static HWND m_hWnd;

	static int m_nX, m_nY;
	static int m_nWidth, m_nHeight;
	static std::string m_strCaption;
	static bool m_bFocus;
};

inline HWND cWindow::GetHwnd() { return m_hWnd; }
inline int cWindow::GetX() { return m_nX; }
inline int cWindow::GetY() { return m_nY; }
inline int cWindow::GetWidth() { return m_nWidth; }
inline int cWindow::GetHeight() { return m_nHeight; }