#include "config.h"

#include "DXenv.h"

DXGI_SWAP_CHAIN_DESC GetSwapChainDescription(HWND hWnd);

DXenv::DXenv(HWND hWnd)
{
	D3D11CreateDeviceAndSwapChain(	NULL,
									D3D_DRIVER_TYPE_HARDWARE,
									NULL,
									NULL,
									NULL,
									NULL,
									D3D11_SDK_VERSION,
									&GetSwapChainDescription(hWnd),
									&m_swapChain,
									&m_device,
									NULL,
									&m_deviceConfig);
}


DXenv& DXenv::operator=(DXenv& env)
{
	m_device		= env.m_device;
	m_deviceConfig	= env.m_deviceConfig;
	m_swapChain		= env.m_swapChain;
	return *this;
}

DXenv::~DXenv()
{
	m_swapChain->Release();
	m_device->Release();
	m_deviceConfig->Release();
}

DXGI_SWAP_CHAIN_DESC GetSwapChainDescription(HWND hWnd)
{
	DXGI_SWAP_CHAIN_DESC description;
	ZeroMemory(&description, sizeof(DXGI_SWAP_CHAIN_DESC));
	description.BufferCount			= 1;                                    
	description.BufferDesc.Format	= DXGI_FORMAT_R8G8B8A8_UNORM;     
	description.BufferUsage			= DXGI_USAGE_RENDER_TARGET_OUTPUT;      
	description.OutputWindow		= hWnd;                                
	description.SampleDesc.Count	= 4;                               
	description.Windowed			= TRUE;                                    
	return description;
}