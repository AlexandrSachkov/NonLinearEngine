#include "stdafx.h"
#include "RenderingDevice\DX11Device\NLREDX11RenderingDevice.h"


D3D11_INPUT_ELEMENT_DESC NLREDX11RenderingDevice::defaultLayout[] = {
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 1, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};


NLREDX11RenderingDevice::NLREDX11RenderingDevice(HWND hwndVal, int screenWidthVal, int screenHeightVal)
{

	_hwnd = hwndVal;
	_screenWidth = screenWidthVal;
	_screenHeight = screenHeightVal;

	maxIndices = 20000;
	maxVertices = 20000;

	SwapChain = NULL;
	d3d11Device = NULL;
	d3d11DevCon = NULL;
	renderTargetView = NULL;
	depthStencilBuffer = NULL;
	depthStencilView = NULL;
	_deviceContext = NULL;

	indexStreamBuff = NULL;
	geomStreamBuff = NULL;
	textCoordStreamBuff = NULL;

	defaultInputLayout = NULL;
	perFrameCBuffer = NULL;
	perObjectCBuffer = NULL;
	defaultTextSamplerState = NULL;
	backFaceCullState = NULL;

	defaultInputLayoutNumElements = 3;

	if (!initialize())
	{
		throw new std::exception("NLREDX11RenderingDevice failed to initialize");
	}
}

NLREDX11RenderingDevice::NLREDX11RenderingDevice(const NLREDX11RenderingDevice& val)
{
}

NLREDX11RenderingDevice::~NLREDX11RenderingDevice()
{
	release();
}

bool NLREDX11RenderingDevice::initialize()
{

	if (_hwnd == NULL)
	{
		NLRE_Log::err(NLRE_Log::ErrorFlag::CRITICAL, "Window was not initialized.");
		return false;
	}
	if (!initializeDirect3d11()) return false;
	//if (!createAllResources()) return false;
	return true;
}
/*bool NLREDX11RenderingDevice::createAllResources()
{

	//if (!createAllShaders())		return false;
	if (!createIndexBuffer())		return false;
	if (!createStreamBuffers())		return false;
	if (!createInputLayouts())		return false;

	setViewPort();

	if (!createPerFrameCBuffer())		return false;
	if (!createPerObjectCBuffer())		return false;
	if (!createTextureSamplerStates())	return false;
	if (!createBlendStates())			return false;
	if (!createRasterizerStates())		return false;

	return true;
}
*/

void NLREDX11RenderingDevice::release()
{
	_deviceContext->Release();

	_vertexShaderMap.clear();
	_vertexShaderBlobMap.clear();
	_pixelShaderMap.clear();
	_pixelShaderBlobMap.clear();

	depthStencilView->Release();
	depthStencilBuffer->Release();
	renderTargetView->Release();
	d3d11DevCon->Release();
	d3d11Device->Release();
	SwapChain->Release();

	indexStreamBuff->Release();
	geomStreamBuff->Release();
	textCoordStreamBuff->Release();

	defaultInputLayout->Release();

	if (perFrameCBuffer) perFrameCBuffer->Release();

	perObjectCBuffer->Release();
	defaultTextSamplerState->Release();
	backFaceCullState->Release();

}

bool NLREDX11RenderingDevice::initializeDirect3d11()
{
	if (!createDeviceAndSwapChain()) return false;
	if (!createRenderTargetView()) return false;
	if (!createDepthStencilView()) return false;
	if (!setRenderTargets()) return false;
	if (!createDeviceContexts()) return false;

	return true;
}
bool NLREDX11RenderingDevice::createDeviceAndSwapChain()
{
	HRESULT hr;

	//Describe our SwapChain Buffer
	DXGI_MODE_DESC bufferDesc;

	ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));

	bufferDesc.Width = _screenWidth;
	bufferDesc.Height = _screenHeight;
	bufferDesc.RefreshRate.Numerator = 60;
	bufferDesc.RefreshRate.Denominator = 1;
	bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	//Describe our SwapChain
	DXGI_SWAP_CHAIN_DESC swapChainDesc;

	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

	swapChainDesc.BufferDesc = bufferDesc;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 1;
	swapChainDesc.OutputWindow = _hwnd;
	swapChainDesc.Windowed = TRUE;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;


	//Create our SwapChain
	hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL,
		D3D11_SDK_VERSION, &swapChainDesc, &SwapChain, &d3d11Device, NULL, &d3d11DevCon);

	if (FAILED(hr))
	{
		NLRE_Log::err(NLRE_Log::ErrorFlag::CRITICAL, "Failed to create DX11 device and swap chain.");
		return false;
	}

	return true;
}
bool NLREDX11RenderingDevice::createRenderTargetView()
{
	HRESULT hr;

	//Create our BackBuffer
	ID3D11Texture2D* BackBuffer;
	hr = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer);

	if (FAILED(hr))
	{
		NLRE_Log::err(NLRE_Log::ErrorFlag::CRITICAL, "Failed to create Back Buffer");
		return false;
	}

	//Create our Render Target
	hr = d3d11Device->CreateRenderTargetView(BackBuffer, NULL, &renderTargetView);
	BackBuffer->Release();

	if (FAILED(hr))
	{
		NLRE_Log::err(NLRE_Log::ErrorFlag::CRITICAL, "Failed to create Render Target View");
		return false;
	}

	return true;
}
bool NLREDX11RenderingDevice::createDepthStencilView()
{
	HRESULT hr;

	//Describe our Depth/Stencil Buffer
	D3D11_TEXTURE2D_DESC depthStencilDesc;

	depthStencilDesc.Width = _screenWidth;
	depthStencilDesc.Height = _screenHeight;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	//Create the Depth/Stencil View
	hr = d3d11Device->CreateTexture2D(&depthStencilDesc, NULL, &depthStencilBuffer);
	if (FAILED(hr))
	{
		NLRE_Log::err(NLRE_Log::ErrorFlag::CRITICAL, "Failed to create depthStencilBuffer");
		return false;
	}

	hr = d3d11Device->CreateDepthStencilView(depthStencilBuffer, NULL, &depthStencilView);

	if (FAILED(hr))
	{
		NLRE_Log::err(NLRE_Log::ErrorFlag::CRITICAL, "Failed to create DepthStencilView");
		return false;
	}

	return true;
}
bool NLREDX11RenderingDevice::setRenderTargets()
{
	//Set our Render Target
	d3d11DevCon->OMSetRenderTargets(1, &renderTargetView, depthStencilView);

	return true;
}
bool NLREDX11RenderingDevice::createDeviceContexts()
{
	HRESULT hr;

	hr = d3d11Device->CreateDeferredContext(0, &_deviceContext);
	if (FAILED(hr))
	{
		NLRE_Log::err(NLRE_Log::ErrorFlag::CRITICAL, "Failed to create Device Context");
		return false;
	}
	return true;
}
/*bool NLREDX11RenderingDevice::createAllShaders()
{
	if (!createVShader(L"Resources/FX/Effects.fx", VS)) return false;
	if (!createPShader(L"Resources/FX/Effects.fx", PS)) return false;

	return true;
}*/
bool NLREDX11RenderingDevice::loadBlobFromFile(std::wstring path, ShaderBlob& blob)
{
	std::ifstream fin(path, std::ios::binary);

	if (!fin) return false;

	fin.seekg(0, std::ios_base::end);
	size_t size = (size_t)fin.tellg();
	fin.seekg(0, std::ios_base::beg);
	std::vector<char> compiledShader(size);
	fin.read(&compiledShader[0], size);
	fin.close();

	blob.data = &compiledShader[0];
	blob.size = size;
	return true;
}

bool NLREDX11RenderingDevice::loadVShader(NLRE_RenderStateId::VS vsId, std::wstring path)
{
	if (_vertexShaderMap.at(vsId)) return true;

	HRESULT hr;

	//Load vertex shader from file
	ShaderBlob blob;
	if (!loadBlobFromFile(path, blob))
	{
		NLRE_Log::err(NLRE_Log::ErrorFlag::CRITICAL, "Failed to load Vertex Shader: ", path);
		return false;
	}

	//add blob to collection
	_vertexShaderBlobMap.insert(std::pair<NLRE_RenderStateId::VS, ShaderBlob>(vsId, blob));

	//Create Vertex Shader
	ID3D11VertexShader* vs = NULL;
	hr = d3d11Device->CreateVertexShader(blob.data, blob.size, NULL, &vs);
	if (FAILED(hr))
	{
		NLRE_Log::err(NLRE_Log::ErrorFlag::CRITICAL, "Failed to create Vertex Shader");
		return false;
	}

	//add shader to collection
	_vertexShaderMap.insert(std::pair<NLRE_RenderStateId::VS, ID3D11VertexShader*>(vsId, vs));

	return true;
}

bool NLREDX11RenderingDevice::loadPShader(NLRE_RenderStateId::PS psId, std::wstring path)
{
	if (_pixelShaderMap.at(psId)) return true;

	HRESULT hr;

	//Load pixel shader from file
	ShaderBlob blob;
	if (!loadBlobFromFile(path, blob))
	{
		NLRE_Log::err(NLRE_Log::ErrorFlag::CRITICAL, "Failed to load Pixel Shader: ", path);
		return false;
	}

	//add blob to collection
	_pixelShaderBlobMap.insert(std::pair<NLRE_RenderStateId::PS, ShaderBlob>(psId, blob));

	//Create Pixel Shader
	ID3D11PixelShader* ps = NULL;
	hr = d3d11Device->CreatePixelShader(blob.data, blob.size, NULL, &ps);
	if (FAILED(hr))
	{
		NLRE_Log::err(NLRE_Log::ErrorFlag::CRITICAL, "Failed to create Pixel Shader");
		return false;
	}

	//add shader to collection
	_pixelShaderMap.insert(std::pair<NLRE_RenderStateId::PS, ID3D11PixelShader*>(psId, ps));

	return true;
}

void NLREDX11RenderingDevice::setVShader(NLRE_RenderStateId::VS vsId)
{
	d3d11DevCon->VSSetShader(_vertexShaderMap.at(vsId),NULL,0);
}

void NLREDX11RenderingDevice::setPShader(NLRE_RenderStateId::PS psId)
{
	d3d11DevCon->PSSetShader(_pixelShaderMap.at(psId), NULL, 0);
}


bool NLREDX11RenderingDevice::createIndexBuffer(NLRE_RenderStateId::Usage usage, DWORD indiceArr[], DWORD arrayLength, NLRE_Buffer* indexBuffer)
{
	HRESULT hr;

	D3D11_BUFFER_DESC indexBufferDesc;
	ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));

	indexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	indexBufferDesc.ByteWidth = sizeof(DWORD)* maxIndices;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	indexBufferDesc.MiscFlags = 0;

	hr = d3d11Device->CreateBuffer(&indexBufferDesc, NULL, &indexStreamBuff);

	if (FAILED(hr))
	{
		NLRE_Log::err(NLRE_Log::ErrorFlag::CRITICAL, "Failed to create Index Buffer");
		return false;
	}
	return true;
}

bool NLREDX11RenderingDevice::createStreamBuffers()
{
	HRESULT hr;

	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));

	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(GeomStr)* maxVertices;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;

	hr = d3d11Device->CreateBuffer(&vertexBufferDesc, NULL, &geomStreamBuff);
	if (FAILED(hr))
	{
		NLRE_Log::err(NLRE_Log::ErrorFlag::CRITICAL, "Failed to create Geometry Stream Buffer");
		return false;
	}


	vertexBufferDesc.ByteWidth = sizeof(TextStr)* maxVertices;
	hr = d3d11Device->CreateBuffer(&vertexBufferDesc, NULL, &textCoordStreamBuff);

	if (FAILED(hr))
	{
		NLRE_Log::err(NLRE_Log::ErrorFlag::CRITICAL, "Failed to create Text Coordinate Stream Buffer");
		return false;
	}
	return true;
}

bool NLREDX11RenderingDevice::createInputLayouts()
{
	HRESULT hr;

	hr = d3d11Device->CreateInputLayout(defaultLayout, defaultInputLayoutNumElements, VS_Buffer->GetBufferPointer(),
		VS_Buffer->GetBufferSize(), &defaultInputLayout);
	if (FAILED(hr))
	{
		NLRE_Log::err(NLRE_Log::ErrorFlag::CRITICAL, "Failed to create Input Layout");
		return false;
	}
	return true;
}

void NLREDX11RenderingDevice::setViewPort()
{
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = _screenWidth;
	viewport.Height = _screenHeight;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	//Set the Viewport
	d3d11DevCon->RSSetViewports(1, &viewport);
}

bool NLREDX11RenderingDevice::createPerFrameCBuffer()
{

	return true;
}

bool NLREDX11RenderingDevice::createPerObjectCBuffer()
{
	HRESULT hr;

	//Create the buffer to send to the cbuffer in effect file
	D3D11_BUFFER_DESC cbbd;
	ZeroMemory(&cbbd, sizeof(D3D11_BUFFER_DESC));

	cbbd.Usage = D3D11_USAGE_DEFAULT;
	cbbd.ByteWidth = sizeof(cbPerObject);
	cbbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbbd.CPUAccessFlags = 0;
	cbbd.MiscFlags = 0;

	hr = d3d11Device->CreateBuffer(&cbbd, NULL, &perObjectCBuffer);
	if (FAILED(hr))
	{
		NLRE_Log::err(NLRE_Log::ErrorFlag::CRITICAL, "Failed to create perObjectCBuffer");
		return false;
	}

	return true;
}

bool NLREDX11RenderingDevice::createTextureSamplerStates()
{
	HRESULT hr;

	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

	//Create the Sample State
	hr = d3d11Device->CreateSamplerState(&sampDesc, &defaultTextSamplerState);
	if (FAILED(hr))
	{
		NLRE_Log::err(NLRE_Log::ErrorFlag::CRITICAL, "Failed to create texture sampler state");
		return false;
	}
	return true;
}

bool NLREDX11RenderingDevice::createBlendStates()
{

	return true;
}

bool NLREDX11RenderingDevice::createRasterizerStates()
{
	HRESULT hr;

	D3D11_RASTERIZER_DESC cmdesc;
	ZeroMemory(&cmdesc, sizeof(D3D11_RASTERIZER_DESC));

	cmdesc.FillMode = D3D11_FILL_SOLID;
	cmdesc.CullMode = D3D11_CULL_NONE;

	hr = d3d11Device->CreateRasterizerState(&cmdesc, &backFaceCullState);
	if (FAILED(hr))
	{
		NLRE_Log::err(NLRE_Log::ErrorFlag::CRITICAL, "Failed to create rasterizer state");
		return false;
	}

	return true;
}

ID3D11Device* NLREDX11RenderingDevice::getD3DDevice()
{
	return d3d11Device;
}
