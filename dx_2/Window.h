#ifndef DX_2_WINDOW_H
#define DX_2_WINDOW_H

class Window
{
public:
	Window(HINSTANCE in_hInstance, HINSTANCE in_hPrevInstance, LPSTR in_lpCmdLine, int in_nCmdShow);
	bool Window::Show();
	HWND GetHandle() const;
	Window& operator=(Window &wind);
	~Window();
private:
	HWND m_hWnd;
	WNDCLASSEX m_wc;  
	int m_nCmdShow;
};

#endif // DX_2_WINDOW_H