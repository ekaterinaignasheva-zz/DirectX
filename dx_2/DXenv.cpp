#include "config.h"

#include "DXenv.h"

DXGI_SWAP_CHAIN_DESC GetSwapChainDescription(HWND hWnd);

char* g_strVS =
"void VS( in float4 posIn : POSITION,\n"
"         out float4 posOut : SV_Position )\n"
"{\n"
"    // Output the vertex position, unchanged\n"
"    posOut = posIn;\n"
"}\n";

char* g_strPS =
"void PS( out float4 colorOut : SV_Target )\n"
"{\n"
"    // Make each pixel yellow, with alpha = 1\n"
"    colorOut = float4( 1.0f, 1.0f, 0.0f, 1.0f );\n"
"}\n";

struct SimpleVertex
{
	FLOAT Pos[3]; // (X, Y, Z) coordinates of each vertex
};

DXenv::DXenv(HWND hWnd)
{
	InitDeviceAndSwapChain(hWnd);
	InitDeviceObjects();
	InitDeviceContext(hWnd);
}

void DXenv::InitDeviceAndSwapChain(HWND hWnd)
{
	HRESULT hr = S_OK;

	RECT rc;
	GetClientRect(hWnd, &rc);
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = _countof(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = _countof(featureLevels);
	D3D_FEATURE_LEVEL featureLevelOut;

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	D3D_DRIVER_TYPE driverType;
	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain(NULL, driverType, NULL, createDeviceFlags,
			featureLevels, numFeatureLevels, D3D11_SDK_VERSION,
			&sd, &m_pSwapChain, &m_pDevice, &featureLevelOut,
			&m_pDeviceContext);
		if (SUCCEEDED(hr))
			break;
	}
}

void DXenv::InitDeviceObjects()
{
	HRESULT hr = S_OK;

	// Create the render target view
	ID3D11Texture2D* pRenderTargetTexture;
	hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pRenderTargetTexture);

	hr = m_pDevice->CreateRenderTargetView(pRenderTargetTexture, NULL, &m_pRenderTargetView);
	pRenderTargetTexture->Release();

	// Compile and create the vertex shader
	DWORD dwShaderFlags = D3D10_SHADER_ENABLE_STRICTNESS;
#ifdef _DEBUG
	dwShaderFlags |= D3D10_SHADER_DEBUG;
#endif
	ID3D10Blob* pBlobVS = NULL;
	ID3D10Blob* pBlobError = NULL;
	hr = D3DCompile(g_strVS, lstrlenA(g_strVS) + 1, "VS", NULL, NULL, "VS",
		"vs_4_0", dwShaderFlags, 0, &pBlobVS, &pBlobError);

	hr = m_pDevice->CreateVertexShader(pBlobVS->GetBufferPointer(), pBlobVS->GetBufferSize(),
		NULL, &m_pVertexShader);

	// Compile and create the pixel shader
	ID3D10Blob* pBlobPS = NULL;
	hr = D3DCompile(g_strPS, lstrlenA(g_strPS) + 1, "PS", NULL, NULL, "PS",
		"ps_4_0", dwShaderFlags, 0, &pBlobPS, &pBlobError);

	hr = m_pDevice->CreatePixelShader(pBlobPS->GetBufferPointer(), pBlobPS->GetBufferSize(),
		NULL, &m_pPixelShader);

	pBlobPS->Release();

	// Create the input layout
	D3D11_INPUT_ELEMENT_DESC elements[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = _countof(elements);

	hr = m_pDevice->CreateInputLayout(elements, numElements, pBlobVS->GetBufferPointer(),
		pBlobVS->GetBufferSize(), &m_pInputLayout);

	pBlobVS->Release();

	// Create the vertex buffer
	SimpleVertex vertices[] =
	{
		0.0f, 0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,
	};
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(vertices);
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = vertices;
	hr = m_pDevice->CreateBuffer(&bd, &initData, &m_pVertexBuffer);
}

void DXenv::InitDeviceContext(HWND hWnd)
{
	m_pDeviceContext->IASetInputLayout(m_pInputLayout);

	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_pDeviceContext->VSSetShader(m_pVertexShader, NULL, 0);

	m_pDeviceContext->PSSetShader(m_pPixelShader, NULL, 0);

	RECT rc;
	GetClientRect(hWnd, &rc);
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)(rc.right - rc.left);
	vp.Height = (FLOAT)(rc.bottom - rc.top);
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	m_pDeviceContext->RSSetViewports(1, &vp);

	m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, NULL);
}

DXenv& DXenv::operator=(DXenv& env)
{
	m_pDevice			= env.m_pDevice;
	m_pDeviceContext	= env.m_pDeviceContext;
	m_pSwapChain		= env.m_pSwapChain;
	return *this;
}

void DXenv::Draw()
{
	// Clear the render target to dark blue
	float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red, green, blue, alpha
	m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, ClearColor);

	// Render a triangle
	m_pDeviceContext->Draw(3, 0);

	// Show the rendered frame on the screen
	m_pSwapChain->Present(0, 0);
}

DXenv::~DXenv()
{
	CleanupDevice();
}

void DXenv::CleanupDevice()
{
	if (m_pVertexShader		!= nullptr)		m_pVertexShader		->Release();
	if (m_pPixelShader		!= nullptr)		m_pPixelShader		->Release();
	if (m_pVertexBuffer		!= nullptr)		m_pVertexBuffer		->Release();
	if (m_pInputLayout		!= nullptr)		m_pInputLayout		->Release();
	if (m_pRenderTargetView != nullptr)		m_pRenderTargetView	->Release();
	if (m_pDeviceContext	!= nullptr)		m_pDeviceContext	->Release();
	if (m_pSwapChain		!= nullptr)		m_pSwapChain		->Release();
	if (m_pDevice			!= nullptr)		m_pDevice			->Release();
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