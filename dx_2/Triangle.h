#pragma once
#include "config.h"
#include "Renderer.h"

#include "Window.h"
#include "DXenv.h"

class Triangle :
	public Renderer
{
public:
	Triangle(Window& wind, DXenv& env);
	Triangle(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
	int StartEventLoop();
	~Triangle();
private:
	Window m_window;
	DXenv m_dxEnv;
};

