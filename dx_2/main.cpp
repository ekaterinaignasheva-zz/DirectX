#include "config.h"

#include <windows.h>

#include "Triangle.h"

int WINAPI WinMain(	HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPSTR lpCmdLine,
					int nCmdShow)
{
	Triangle renderer(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	renderer.StartEventLoop();
}
