#ifndef DX_2_TRIANGLE_H
#define DX_2_TRIANGLE_H

#include "Renderer.h"

class Window;
class DXenv;

class Triangle :
	public Renderer
{
public:
	Triangle(shared_ptr<Window> wind, shared_ptr<DXenv> env);
	Triangle(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
	int StartEventLoop();
	~Triangle();
private:
	shared_ptr<Window> m_window;
	shared_ptr<DXenv> m_dxEnv;
};

#endif // DX_2_TRIANGLE_H