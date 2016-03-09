#include "config.h"

#include "Window.h"
#include "DXenv.h"

#include "Triangle.h"

Triangle::Triangle(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	m_window = make_shared<Window>(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	m_dxEnv = make_shared<DXenv>(m_window->GetHandle());
}


Triangle::Triangle(shared_ptr<Window> wind, shared_ptr<DXenv> env)
{
	m_window = wind;
	m_dxEnv = env;	
}

int Triangle::StartEventLoop()
{
	m_window->Show();

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
		}
	}

	return msg.wParam;
}


Triangle::~Triangle()
{
}
