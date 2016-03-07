#pragma once
class Window
{
public:
	Window() = default;
	Window(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine);
	bool Window::Show(int nCmdShow);
	HWND GetHandle();
	Window& operator=(Window &wind);
	~Window();
private:
	HWND m_hWnd;
	WNDCLASSEX m_wc;  
};

