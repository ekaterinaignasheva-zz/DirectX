#include "Triangle.h"

Triangle::Triangle(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow):
m_window(hInstance, hPrevInstance, lpCmdLine), m_dxEnv(m_window.GetHandle())
{
//	m_window = Window(hInstance, hPrevInstance, lpCmdLine);
//	m_dxEnv = DXenv(m_window.GetHandle());
	m_window.Show(nCmdShow);
}


Triangle::Triangle(Window& wind, DXenv& env)
{
	m_window = wind;
	m_dxEnv = env;	
}

int Triangle::StartEventLoop()
{

	MSG msg;

	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
				break;
		}
		else
		{
			// Run game code here
			// ...
			// ...
		}
	}

	return msg.wParam;
}


Triangle::~Triangle()
{
}
