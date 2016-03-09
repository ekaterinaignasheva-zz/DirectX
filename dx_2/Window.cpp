#include "config.h"

#include "Window.h"

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

Window::Window(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ZeroMemory(&m_wc, sizeof(WNDCLASSEX));

	m_wc.cbSize = sizeof(WNDCLASSEX);
	m_wc.style = CS_HREDRAW | CS_VREDRAW;
	m_wc.lpfnWndProc = WindowProc;
	m_wc.hInstance = hInstance;
	m_wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	m_wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	m_wc.lpszClassName = L"WindowClass";

	RegisterClassEx(&m_wc);

	RECT wr = { 0, 0, 800, 600 };
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

	m_hWnd = CreateWindowEx(NULL,
							L"WindowClass",
							L"Our First Direct3D Program",
							WS_OVERLAPPEDWINDOW,
							200,
							200,
							wr.right - wr.left,
							wr.bottom - wr.top,
							NULL,
							NULL,
							hInstance,
							NULL);
	m_nCmdShow = nCmdShow;
}


bool Window::Show()
{
	return ShowWindow(m_hWnd, m_nCmdShow) ? true : false;
}


HWND Window::GetHandle() const
{
	return m_hWnd;
}

Window& Window::operator=(Window &wind)
{
	m_hWnd	= wind.m_hWnd;
	m_wc	= wind.m_wc;
	return *this;
}

Window::~Window()
{
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:  
	{
		PostQuitMessage(0);
		return 0;
	} break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}