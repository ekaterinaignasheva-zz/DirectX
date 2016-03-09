#ifndef DX_2_RENDERER_H
#define DX_2_RENDERER_H

class Renderer
{
public:
	virtual int StartEventLoop() = 0;
	virtual ~Renderer() = default;
};

#endif // DX_2_RENDERER_H