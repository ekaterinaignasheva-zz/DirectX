#pragma once

class Renderer
{
public:
	virtual int StartEventLoop() = 0;
	virtual ~Renderer() = default;
};

