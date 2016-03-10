#ifndef DX_2_DXENV_H
#define DX_2_DXENV_H

class DXenv
{
public:
	DXenv() = default;
	DXenv(HWND hWnd);
	DXenv& operator=(DXenv& env);
	~DXenv();
	void InitDeviceAndSwapChain(HWND hWnd);
	void InitDeviceObjects();
	void InitDeviceContext(HWND hWnd);
	void CleanupDevice();
	void Draw();

private:
	IDXGISwapChain*				m_pSwapChain			= nullptr;
	ID3D11Device*				m_pDevice				= nullptr;
	ID3D11DeviceContext*		m_pDeviceContext		= nullptr;
	ID3D11RenderTargetView*     m_pRenderTargetView		= nullptr;
	ID3D11InputLayout*          m_pInputLayout			= nullptr;
	ID3D11Buffer*               m_pVertexBuffer			= nullptr;
	ID3D11VertexShader*         m_pVertexShader			= nullptr;
	ID3D11PixelShader*          m_pPixelShader			= nullptr;
};

#endif // DX_2_DXENV_H