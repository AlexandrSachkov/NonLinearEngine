#include "stdafx.h"
#include "RenderingDevice\DX11Device\NLREDX11RenderingDevice.h"


NLREDX11RenderingDevice::NLREDX11RenderingDevice(HWND hwndVal, int screenWidthVal, int screenHeightVal)
{

	_hwnd = hwndVal;
	_screenWidth = screenWidthVal;
	_screenHeight = screenHeightVal;

	_d3d11Device = NULL;
	_d3d11DevCon = NULL;
	_swapChain = NULL;

	if (!initialize())
	{
		NLRE_Log::err(NLRE_Log::CRITICAL, "NLREDX11RenderingDevice failed to initialize");
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
	if (!createDeviceAndSwapChain()) return false;
	return true;
}

void NLREDX11RenderingDevice::release()
{
	_d3d11DevCon->Release();
	_d3d11Device->Release();
	_swapChain->Release();
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

	UINT creationFlags = 0;
#ifdef _DEBUG || DEBUG
	creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	//Create our SwapChain
	hr = D3D11CreateDeviceAndSwapChain(
		NULL, 
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		creationFlags,
		NULL, 
		NULL,
		D3D11_SDK_VERSION, 
		&swapChainDesc, 
		&_swapChain, 
		&_d3d11Device, 
		NULL, 
		&_d3d11DevCon);

	if (FAILED(hr))
	{
		NLRE_Log::err(NLRE_Log::ErrorFlag::CRITICAL, "Failed to create DX11 device and swap chain.");
		return false;
	}

	return true;
}

bool NLREDX11RenderingDevice::createBackBufferRenderTargetView(NLRE_APIRenderTargetView*& renderTargetView)
{
	HRESULT hr;

	//Create our BackBuffer
	ID3D11Texture2D* BackBuffer;
	hr = _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer);

	if (FAILED(hr))
	{
		NLRE_Log::err(NLRE_Log::ErrorFlag::CRITICAL, "Failed to get Back Buffer");
		return false;
	}

	//Create our Render Target
	hr = _d3d11Device->CreateRenderTargetView(BackBuffer, NULL, &renderTargetView);
	BackBuffer->Release();

	if (FAILED(hr))
	{
		NLRE_Log::err(NLRE_Log::ErrorFlag::CRITICAL, "Failed to create Back Buffer Render Target View");
		return false;
	}

	return true;
}

bool NLREDX11RenderingDevice::createBlendStates(
	bool enableBlend,
	bool enableIndependentBlending,
	unsigned int numRenderTargets,
	bool enableAlphaToCoverage,
	NLRE_APIBlendState*& blendState)
{
	HRESULT hr;

	if (numRenderTargets > 8)
	{
		NLRE_Log::err(NLRE_Log::CRITICAL, "Failed to create blend state, invalid number of targets: ", numRenderTargets);
		return false;
	}

	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(blendDesc));

	D3D11_RENDER_TARGET_BLEND_DESC rtbd;
	ZeroMemory(&rtbd, sizeof(rtbd));

	rtbd.BlendEnable = enableBlend;
	rtbd.SrcBlend = D3D11_BLEND_SRC_COLOR;
	rtbd.DestBlend = D3D11_BLEND_BLEND_FACTOR;
	rtbd.BlendOp = D3D11_BLEND_OP_ADD;
	rtbd.SrcBlendAlpha = D3D11_BLEND_ONE;
	rtbd.DestBlendAlpha = D3D11_BLEND_ZERO;
	rtbd.BlendOpAlpha = D3D11_BLEND_OP_ADD;
	rtbd.RenderTargetWriteMask = D3D10_COLOR_WRITE_ENABLE_ALL;

	blendDesc.IndependentBlendEnable = enableIndependentBlending;
	blendDesc.AlphaToCoverageEnable = enableAlphaToCoverage;

	if (enableIndependentBlending)
	{
		for (int i = 0; i < numRenderTargets; i++)
		{
			blendDesc.RenderTarget[i] = rtbd;
		}
	}
	else
	{
		blendDesc.RenderTarget[0] = rtbd;
	}


	hr = _d3d11Device->CreateBlendState(&blendDesc, &blendState);
	if (FAILED(hr))
	{
		NLRE_Log::err(NLRE_Log::CRITICAL, "Failed to create blend state");
		return false;
	}
	return true;
}

bool NLREDX11RenderingDevice::createRenderTargetViews(unsigned int numViews, NLRE_APIRenderTargetView*& renderTargetViewArr)
{
	HRESULT hr;

	D3D11_TEXTURE2D_DESC textDesc;
	ZeroMemory(&textDesc, sizeof(textDesc));

	textDesc.Width = _screenWidth;
	textDesc.Height = _screenHeight;
	textDesc.MipLevels = 1;
	textDesc.ArraySize = numViews;
	textDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	textDesc.SampleDesc.Count = 1;
	textDesc.SampleDesc.Quality = 0;
	textDesc.Usage = D3D11_USAGE_DEFAULT;
	textDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	textDesc.CPUAccessFlags = 0;
	textDesc.MiscFlags = 0;

	ID3D11Texture2D* buffer = NULL;
	//Create the Depth/Stencil View
	hr = _d3d11Device->CreateTexture2D(&textDesc, NULL, &buffer);
	if (FAILED(hr))
	{
		NLRE_Log::err(NLRE_Log::ErrorFlag::CRITICAL, "Failed to create Render Target Buffer");
		return false;
	}

	//Create our Render Target
	hr = _d3d11Device->CreateRenderTargetView(buffer, NULL, &renderTargetViewArr);
	buffer->Release();

	if (FAILED(hr))
	{
		NLRE_Log::err(NLRE_Log::ErrorFlag::CRITICAL, "Failed to create Back Buffer Render Target View");
		return false;
	}

	return true;
}

bool NLREDX11RenderingDevice::createDepthStencilView(NLRE_APIDepthStencilView*& depthStencilView)
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
	ID3D11Texture2D* buffer = NULL;
	hr = _d3d11Device->CreateTexture2D(&depthStencilDesc, NULL, &buffer);
	if (FAILED(hr))
	{
		NLRE_Log::err(NLRE_Log::ErrorFlag::CRITICAL, "Failed to create depthStencilBuffer");
		return false;
	}
	hr = _d3d11Device->CreateDepthStencilView(buffer, NULL, &depthStencilView);
	buffer->Release();

	if (FAILED(hr))
	{
		NLRE_Log::err(NLRE_Log::ErrorFlag::CRITICAL, "Failed to create DepthStencilView");
		return false;
	}

	return true;
}

bool NLREDX11RenderingDevice::createShaderResourceViewFromTexture2D(NLRE_APITexture2D* texture, NLRE_APIShaderResourceView*& resourceView)
{
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM; //changes based on the image format
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = -1;
	srvDesc.Texture2D.MostDetailedMip = 0;

	HRESULT hr;
	hr = _d3d11Device->CreateShaderResourceView(texture, &srvDesc, &resourceView);
	if (FAILED(hr))
	{
		NLRE_Log::err(NLRE_Log::REG, "Failed to create Shader Resource View from Texture2D");
		return false;
	}
	return true;
}

bool NLREDX11RenderingDevice::createTexture2D(
	unsigned int width, 
	unsigned int height, 
	bool generateMipMaps, 
	unsigned int MSAALevel, 
	NLRE_USAGE usage, 
	NLRE_BIND_FLAG bindFlag, 
	void* data, 
	unsigned int memPitch,
	NLRE_APITexture2D*& texture)
{
	D3D11_TEXTURE2D_DESC textDesc;
	ZeroMemory(&textDesc, sizeof(textDesc));
	textDesc.Width = width;
	textDesc.Height = height;
	textDesc.MipLevels = generateMipMaps == true ? 0 : 1;
	textDesc.ArraySize = 1;
	textDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM; //needs to change based on texture format

	DXGI_SAMPLE_DESC sampleDesc;
	ZeroMemory(&sampleDesc, sizeof(sampleDesc));
	sampleDesc.Count = MSAALevel;
	sampleDesc.Quality = D3D11_STANDARD_MULTISAMPLE_PATTERN;

	textDesc.SampleDesc = sampleDesc;
	textDesc.Usage = (D3D11_USAGE)usage;
	textDesc.BindFlags = bindFlag;
	textDesc.CPUAccessFlags = usage == NLRE_USAGE_DYNAMIC ? D3D11_CPU_ACCESS_WRITE : 0;
	textDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA subresData;
	ZeroMemory(&subresData, sizeof(subresData));
	subresData.pSysMem = data;
	subresData.SysMemPitch = memPitch;

	HRESULT hr;
	hr = _d3d11Device->CreateTexture2D(&textDesc, &subresData, &texture);
	if (FAILED(hr))
	{
		NLRE_Log::err(NLRE_Log::REG, "Failed to create texture");
		return false;
	}

	//================================== TEMP FORMAT TEST ======================================




	return true;
}


bool NLREDX11RenderingDevice::loadBlobFromFile(std::wstring path, NLRE_ShaderBlob*& blob)
{
	HRESULT hr;

	hr = D3DReadFileToBlob(path.c_str(), &blob);
	if (FAILED(hr)) return false;
	return true;
}


bool NLREDX11RenderingDevice::loadVertexShader(std::wstring path, NLRE_VertexShader& vertexShader)
{
	HRESULT hr;
	//Load vertex shader from file
	if (!loadBlobFromFile(path, vertexShader.blob))
	{
		NLRE_Log::err(NLRE_Log::ErrorFlag::CRITICAL, "Failed to load Vertex Shader: ", path);
		return false;
	}

	//Create Vertex Shader
	hr = _d3d11Device->CreateVertexShader(vertexShader.blob->GetBufferPointer(), vertexShader.blob->GetBufferSize(), NULL, &vertexShader.apiVertexShader);
	if (FAILED(hr))
	{
		NLRE_Log::err(NLRE_Log::ErrorFlag::CRITICAL, "Failed to create Vertex Shader");
		return false;
	}

	return true;
}

bool NLREDX11RenderingDevice::loadPixelShader(std::wstring path, NLRE_PixelShader& pixelShader)
{
	HRESULT hr;

	//Load pixel shader from file
	if (!loadBlobFromFile(path, pixelShader.blob))
	{
		NLRE_Log::err(NLRE_Log::ErrorFlag::CRITICAL, "Failed to load Pixel Shader: ", path);
		return false;
	}

	//Create Pixel Shader
	ID3D11PixelShader* ps = NULL;
	hr = _d3d11Device->CreatePixelShader(pixelShader.blob->GetBufferPointer(), pixelShader.blob->GetBufferSize(), NULL, &pixelShader.apiPixelShader);
	if (FAILED(hr))
	{
		NLRE_Log::err(NLRE_Log::ErrorFlag::CRITICAL, "Failed to create Pixel Shader");
		return false;
	}

	return true;
}

bool NLREDX11RenderingDevice::createInputLayout(NLRE_InputLayoutDesc& ilDesc, NLRE_VertexShader& vShader, NLRE_APIInputLayout*& inputLayout)
{
	HRESULT hr;
	hr = _d3d11Device->CreateInputLayout(ilDesc.apiInputLayoutDesc, ilDesc.numberElements, vShader.blob->GetBufferPointer(),
		vShader.blob->GetBufferSize(), &inputLayout);
	if (FAILED(hr))
	{
		NLRE_Log::err(NLRE_Log::ErrorFlag::CRITICAL, "Failed to create Input Layout");
		return false;
	}
	return true;
}

bool NLREDX11RenderingDevice::createTextureSamplerState(NLRE_APISamplerState*& samplerState)
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
	hr = _d3d11Device->CreateSamplerState(&sampDesc, &samplerState);
	if (FAILED(hr))
	{
		NLRE_Log::err(NLRE_Log::ErrorFlag::CRITICAL, "Failed to create texture sampler state");
		return false;
	}

	return true;
}



bool NLREDX11RenderingDevice::createRasterizerState(NLRE_CULL_MODE cullMode, NLRE_FILL_MODE fillMode, NLRE_APIRasterizerState*& rasterizerState)
{
	HRESULT hr;

	D3D11_RASTERIZER_DESC cmdesc;
	ZeroMemory(&cmdesc, sizeof(D3D11_RASTERIZER_DESC));

	cmdesc.CullMode = (D3D11_CULL_MODE)cullMode;
	cmdesc.FillMode = (D3D11_FILL_MODE)fillMode;

	hr = _d3d11Device->CreateRasterizerState(&cmdesc, &rasterizerState);
	if (FAILED(hr))
	{
		NLRE_Log::err(NLRE_Log::ErrorFlag::CRITICAL, "Failed to create rasterizer state");
		return false;
	}

	return true;
}

