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


	//Create our SwapChain
	hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL,
		D3D11_SDK_VERSION, &swapChainDesc, &_swapChain, &_d3d11Device, NULL, &_d3d11DevCon);

	if (FAILED(hr))
	{
		NLRE_Log::err(NLRE_Log::ErrorFlag::CRITICAL, "Failed to create DX11 device and swap chain.");
		return false;
	}

	return true;
}

bool NLREDX11RenderingDevice::createBackBufferRenderTargetView(NLRE_APIRenderTargetView* renderTargetView)
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
	NLRE_APIBlendState* blendState)
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

bool NLREDX11RenderingDevice::createRenderTargetViews(unsigned int numViews, NLRE_APIRenderTargetView* renderTargetViewArr)
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

bool NLREDX11RenderingDevice::createDepthStencilView(NLRE_APIDepthStencilView* depthStencilView)
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

inline void NLREDX11RenderingDevice::setRenderTargets(
	unsigned int numRenderTargets,
	NLRE_APIRenderTargetView* renderTargerViewArr,
	NLRE_APIDepthStencilView* depthStencilView)
{
	_d3d11DevCon->OMSetRenderTargets(numRenderTargets, &renderTargerViewArr, depthStencilView);
}

bool NLREDX11RenderingDevice::loadBlobFromFile(std::wstring path, NLRE_ShaderBlob& blob)
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

bool NLREDX11RenderingDevice::loadVertexShader(std::wstring path, NLRE_VertexShader& vertexShader)
{
	HRESULT hr;

	//Load vertex shader from file
	NLRE_ShaderBlob blob;
	if (!loadBlobFromFile(path, blob))
	{
		NLRE_Log::err(NLRE_Log::ErrorFlag::CRITICAL, "Failed to load Vertex Shader: ", path);
		return false;
	}

	//Create Vertex Shader
	ID3D11VertexShader* vs = NULL;
	hr = _d3d11Device->CreateVertexShader(blob.data, blob.size, NULL, &vs);
	if (FAILED(hr))
	{
		NLRE_Log::err(NLRE_Log::ErrorFlag::CRITICAL, "Failed to create Vertex Shader");
		return false;
	}
	vertexShader.apiVertexShader = vs;
	vertexShader.blob = blob;

	return true;
}

bool NLREDX11RenderingDevice::loadPixelShader(std::wstring path, NLRE_PixelShader& pixelShader)
{
	HRESULT hr;

	//Load pixel shader from file
	NLRE_ShaderBlob blob;
	if (!loadBlobFromFile(path, blob))
	{
		NLRE_Log::err(NLRE_Log::ErrorFlag::CRITICAL, "Failed to load Pixel Shader: ", path);
		return false;
	}

	//Create Pixel Shader
	ID3D11PixelShader* ps = NULL;
	hr = _d3d11Device->CreatePixelShader(blob.data, blob.size, NULL, &ps);
	if (FAILED(hr))
	{
		NLRE_Log::err(NLRE_Log::ErrorFlag::CRITICAL, "Failed to create Pixel Shader");
		return false;
	}
	pixelShader.apiPixelShader = ps;
	pixelShader.blob = blob;

	return true;
}

bool NLREDX11RenderingDevice::loadTexture(
	std::wstring path,
	NLRE_USAGE usage,
	NLRE_BIND_FLAG bindFlag,
	NLRE_APIResource* texture,
	NLRE_APIShaderResourceView* resourceView)
{
	HRESULT hr;

	std::wstring fileExt = path.substr(path.find_last_of(L"."));

	if (fileExt == L".DDS" || fileExt == L".dds") {

		hr = DirectX::CreateDDSTextureFromFileEx(
			_d3d11Device,
			_d3d11DevCon,
			path.c_str(),
			0,
			(D3D11_USAGE)usage,
			bindFlag,
			usage == NLRE_USAGE_DYNAMIC ? D3D11_CPU_ACCESS_WRITE : 0,
			0,
			false,
			&texture,
			&resourceView
			);
	}
	else
	{
		hr = DirectX::CreateWICTextureFromFileEx(
			_d3d11Device,
			_d3d11DevCon,
			path.c_str(),
			0,
			(D3D11_USAGE)usage,
			bindFlag,
			usage == NLRE_USAGE_DYNAMIC ? D3D11_CPU_ACCESS_WRITE : 0,
			0,
			false,
			&texture,
			&resourceView
			);
	}

	if (FAILED(hr))
	{
		NLRE_Log::err(NLRE_Log::ErrorFlag::CRITICAL, "Texture failed to load: ", path);
		return false;
	}
	return true;
}

inline void NLREDX11RenderingDevice::VSSetShaderResources(unsigned int startSlot, unsigned int numViews, NLRE_APIShaderResourceView* resourceViewArr)
{
	_d3d11DevCon->VSSetShaderResources(startSlot, numViews, &resourceViewArr);
}

inline void NLREDX11RenderingDevice::PSSetShaderResources(unsigned int startSlot, unsigned int numViews, NLRE_APIShaderResourceView* resourceViewArr)
{
	_d3d11DevCon->PSSetShaderResources(startSlot, numViews, &resourceViewArr);
}

inline void NLREDX11RenderingDevice::GSSetShaderResources(unsigned int startSlot, unsigned int numViews, NLRE_APIShaderResourceView* resourceViewArr)
{
	_d3d11DevCon->GSSetShaderResources(startSlot, numViews, &resourceViewArr);
}

inline void NLREDX11RenderingDevice::setVertexShader(const NLRE_VertexShader& vertexShader)
{
	_d3d11DevCon->VSSetShader(vertexShader.apiVertexShader, NULL, 0);
}

inline void NLREDX11RenderingDevice::setPixelShader(const NLRE_PixelShader& pixelShader)
{
	_d3d11DevCon->PSSetShader(pixelShader.apiPixelShader, NULL, 0);
}

inline void NLREDX11RenderingDevice::setBlendState(NLRE_APIBlendState* blendState, float blendFactor[])
{
	_d3d11DevCon->OMSetBlendState(blendState, blendFactor, 0xffffffff);
}

template<class DataType>
bool NLREDX11RenderingDevice::createBuffer(
	NLRE_BIND_FLAG bindFlag,
	NLRE_USAGE usage,
	DataType dataArr[],
	size_t arrayLength,
	NLRE_Buffer& buffer)
{
	HRESULT hr;

	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));


	bufferDesc.BindFlags = bindFlag;
	bufferDesc.Usage = usage;

	if (usage == NLRE_USAGE_DYNAMIC)
	{
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	else
	{
		bufferDesc.CPUAccessFlags = 0;
	}

	bufferDesc.ByteWidth = sizeof(DataType)* arrayLength;
	bufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA subresData;
	ZeroMemory(&subresData, sizeof(subresData));
	subresData.pSysMem = dataArr;

	ID3D11Buffer* apiBuffer = NULL;
	hr = _d3d11Device->CreateBuffer(&bufferDesc, &subresData, &apiBuffer);

	if (FAILED(hr))
	{
		NLRE_Log::err(NLRE_Log::ErrorFlag::CRITICAL, "Failed to create Buffer Type: ", buffType, ", Usage: ", usage);
		return false;
	}
	NLRE_Buffer buffer;
	buffer.apiBuffer = apiBuffer;
	buffer.type = buffType;
	buffer.usage = usage;
	buffer.elementSize = sizeof(DataType);

	return true;
}

inline void NLREDX11RenderingDevice::VSSetConstantBuffer(unsigned int startSlot, unsigned int numBuffers, const NLRE_Buffer& buffer)
{
	_d3d11DevCon->VSSetConstantBuffers(startSlot, numBuffers, &(buffer.apiBuffer));
}

inline void NLREDX11RenderingDevice::PSSetConstantBuffer(unsigned int startSlot, unsigned int numBuffers, const NLRE_Buffer& buffer)
{
	_d3d11DevCon->PSSetConstantBuffers(startSlot, numBuffers, &(buffer.apiBuffer));
}

inline void NLREDX11RenderingDevice::GSSetConstantBuffer(unsigned int startSlot, unsigned int numBuffers, const NLRE_Buffer& buffer)
{
	_d3d11DevCon->GSSetConstantBuffers(startSlot, numBuffers, &(buffer.apiBuffer));
}

inline void NLREDX11RenderingDevice::setVertexBuffer(const NLRE_Buffer& buffer, unsigned int slotNum)
{
	_d3d11DevCon->IASetVertexBuffers(slotNum, 1, &(buffer.apiBuffer), &(buffer.elementSize), 0);
}

inline void NLREDX11RenderingDevice::setIndexBuffer(const NLRE_Buffer& buffer)
{
	_d3d11DevCon->IASetIndexBuffer(buffer.apiBuffer, DXGI_FORMAT_R32_UINT, 0);
}

bool NLREDX11RenderingDevice::createInputLayout(NLRE_InputLayoutDesc ilDesc, NLRE_VertexShader vShader, NLRE_APIInputLayout* inputLayout)
{
	HRESULT hr;

	hr = _d3d11Device->CreateInputLayout(ilDesc.apiInputLayoutDesc, ilDesc.numberElements, vShader.blob.data,
		vShader.blob.size, &inputLayout);
	if (FAILED(hr))
	{
		NLRE_Log::err(NLRE_Log::ErrorFlag::CRITICAL, "Failed to create Input Layout");
		return false;
	}
	return true;
}

inline void NLREDX11RenderingDevice::setInputLayout(NLRE_APIInputLayout* inputLayout)
{
	_d3d11DevCon->IASetInputLayout(inputLayout);
}

inline void NLREDX11RenderingDevice::setPrimitiveTopology(NLRE_PRIMITIVE_TOPOLOGY primitiveTopology)
{
	_d3d11DevCon->IASetPrimitiveTopology((D3D11_PRIMITIVE_TOPOLOGY)primitiveTopology);
}

inline void NLREDX11RenderingDevice::setViewPort(int numViewports, int x, int y, int width, int height, float minDepth, float maxDepth)
{
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = x;
	viewport.TopLeftY = y;
	viewport.Width = width;
	viewport.Height = height;
	viewport.MinDepth = minDepth;
	viewport.MaxDepth = maxDepth;

	//Set the Viewport
	_d3d11DevCon->RSSetViewports(numViewports, &viewport);
}

bool NLREDX11RenderingDevice::createTextureSamplerState(NLRE_APISamplerState* samplerState)
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

inline void NLREDX11RenderingDevice::VSSetTextureSamplerState(unsigned int startSlot, unsigned int numStates, NLRE_APISamplerState* samplerState)
{
	_d3d11DevCon->VSSetSamplers(startSlot, numStates, &samplerState);
}

inline void NLREDX11RenderingDevice::PSSetTextureSamplerState(unsigned int startSlot, unsigned int numStates, NLRE_APISamplerState* samplerState)
{
	_d3d11DevCon->PSSetSamplers(startSlot, numStates, &samplerState);
}

inline void NLREDX11RenderingDevice::GSSetTextureSamplerState(unsigned int startSlot, unsigned int numStates, NLRE_APISamplerState* samplerState)
{
	_d3d11DevCon->GSSetSamplers(startSlot, numStates, &samplerState);
}

bool NLREDX11RenderingDevice::createRasterizerState(NLRE_CULL_MODE cullMode, NLRE_FILL_MODE fillMode, NLRE_APIRasterizerState* rasterizerState)
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

inline void NLREDX11RenderingDevice::setRasterizerState(NLRE_APIRasterizerState* rasterizerState)
{
	_d3d11DevCon->RSSetState(rasterizerState);
}

inline void NLREDX11RenderingDevice::clearRenderTargetView(NLRE_APIRenderTargetView* renderTargetView, float colorRGBA[])
{
	_d3d11DevCon->ClearRenderTargetView(renderTargetView, colorRGBA);
}

inline void NLREDX11RenderingDevice::clearDepthStencilView(NLRE_APIDepthStencilView* depthStencilView)
{
	_d3d11DevCon->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

inline void NLREDX11RenderingDevice::display()
{
	_swapChain->Present(0, 0);
}