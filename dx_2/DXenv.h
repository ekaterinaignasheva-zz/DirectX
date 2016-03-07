#pragma once
class DXenv
{
public:
	DXenv() = default;
	DXenv(HWND hWnd);
	DXenv& operator=(DXenv& env);
	~DXenv();
private:
	IDXGISwapChain		*m_swapChain;       
	ID3D11Device		*m_device;               
	ID3D11DeviceContext *m_deviceConfig;     
};

