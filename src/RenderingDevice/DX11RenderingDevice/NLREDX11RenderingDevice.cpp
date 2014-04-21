#include "stdafx.h"
#include "RenderingDevice\DX11Device\NLREDX11RenderingDevice.h"

D3D11_INPUT_ELEMENT_DESC RenderingDevice::defaultLayout[] = {
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },  
	{ "NORMAL", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },  
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 1, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }, 
};

RenderingDevice::RenderingDevice()
{
	renameDevice("RenderingDevice");
	initialized = false;

	hwnd = NULL;
	Width = 0;
	Height = 0;

	numRenderingThreads = 2;
	numDeferredContexts = numRenderingThreads - 1;
	maxIndices = 20000;
	maxVertices = 20000;

	SwapChain = NULL;
	d3d11Device = NULL;
	d3d11DevCon = NULL;
	renderTargetView = NULL;
	depthStencilBuffer = NULL;
	depthStencilView = NULL;
	deferredContextArr = NULL;

	VS_Buffer = NULL;
	PS_Buffer = NULL;
	VS = NULL;
	PS = NULL;

	indexStreamBuff = NULL;
	geomStreamBuff = NULL;
	textCoordStreamBuff = NULL;

	defaultInputLayout = NULL;
	perFrameCBuffer = NULL;
	perObjectCBuffer = NULL;
	defaultTextSamplerState = NULL;
	backFaceCullState = NULL;

	defaultInputLayoutNumElements = 3;
}

RenderingDevice::RenderingDevice(const RenderingDevice& val)
{
}

RenderingDevice::~RenderingDevice()
{
	release();
}

ResultInfo RenderingDevice::initialize(HWND hwndVal,int widthVal, int heightVal)
{
	ResultInfo result;
	if (initialized) return result;

	if(hwndVal == NULL)
	{
		result.failed(this,"Initialize Window prior to the Rendering Engine");
		return result;
	}
	hwnd = hwndVal;
	Width = widthVal;
	Height = heightVal;

	result = initializeDirect3d11();
	result.extendPath(this);
	if(!result.ok()) return result;

	result = createAllResources();
	result.extendPath(this);
	if(!result.ok()) return result;

	initialized = true;
	return result;
}
ResultInfo RenderingDevice::createAllResources()
{
	ResultInfo result;

	result = createAllShaders();
	result.extendPath(this);
	if(!result.ok()) return result;

	result = createIndexBuffer();
	result.extendPath(this);
	if(!result.ok()) return result;

	result = createStreamBuffers();
	result.extendPath(this);
	if(!result.ok()) return result;

	result = createInputLayouts();
	result.extendPath(this);
	if(!result.ok()) return result;

	setViewPort();

	result = createPerFrameCBuffer();
	result.extendPath(this);
	if(!result.ok()) return result;

	result = createPerObjectCBuffer();
	result.extendPath(this);
	if(!result.ok()) return result;

	result = createTextureSamplerStates();
	result.extendPath(this);
	if(!result.ok()) return result;

	result = createBlendStates();
	result.extendPath(this);
	if(!result.ok()) return result;

	result = createRasterizerStates();
	result.extendPath(this);

	return result;
}
bool RenderingDevice::isInitialized()
{
	return initialized;
}
void RenderingDevice::release()
{
	if(!initialized) return;

	if(deferredContextArr != NULL)
	{
		for(int i = 0; i < numDeferredContexts; i++)
		{
			deferredContextArr[i]->Release();
		}
	}

	if(VS) VS->Release();
	if(PS) PS->Release();


	depthStencilView->Release();
	depthStencilBuffer->Release();
	renderTargetView->Release();
	d3d11DevCon->Release();
	d3d11Device->Release();
	SwapChain->Release();

	
	VS_Buffer->Release();
	PS_Buffer->Release();
	

	indexStreamBuff->Release();
	geomStreamBuff->Release();
	textCoordStreamBuff->Release();

	defaultInputLayout->Release();

	if(perFrameCBuffer) perFrameCBuffer->Release();

	perObjectCBuffer->Release();
	defaultTextSamplerState->Release();
	backFaceCullState->Release();

	initialized = false;
}

ResultInfo RenderingDevice::initializeDirect3d11()
{
	ResultInfo result;

	result = createDeviceAndSwapChain();
	result.extendPath(this);
	if(!result.ok()) return result;

	result = createRenderTargetView();
	result.extendPath(this);
	if(!result.ok()) return result;

	result = createDepthStencilView();
	result.extendPath(this);
	if(!result.ok()) return result;

	result = setRenderTargets();
	result.extendPath(this);
	if(!result.ok()) return result;

	result = createDeferredContexts();
	result.extendPath(this);
	
	return result;
}
ResultInfo RenderingDevice::createDeviceAndSwapChain()
{
	ResultInfo result;
	HRESULT hr;

	//Describe our SwapChain Buffer
	DXGI_MODE_DESC bufferDesc;

	ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));

	bufferDesc.Width = Width;
	bufferDesc.Height = Height;
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
	swapChainDesc.OutputWindow = hwnd; 
	swapChainDesc.Windowed = TRUE; 
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;


	//Create our SwapChain
	hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL,
		D3D11_SDK_VERSION, &swapChainDesc, &SwapChain, &d3d11Device, NULL, &d3d11DevCon);

	if(FAILED(hr)) result.failed(this,"Failed to create swap chain");

	return result;
}
ResultInfo RenderingDevice::createRenderTargetView()
{
	ResultInfo result;
	HRESULT hr;

	//Create our BackBuffer
	ID3D11Texture2D* BackBuffer;
	hr = SwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), (void**)&BackBuffer );

	if(FAILED(hr))
	{
		result.failed(this,"Failed to create Back Buffer");
		return result;
	}

	//Create our Render Target
	hr = d3d11Device->CreateRenderTargetView( BackBuffer, NULL, &renderTargetView );
	BackBuffer->Release();

	if(FAILED(hr)) result.failed(this,"Failed to create Render Target View");

	return result;
}
ResultInfo RenderingDevice::createDepthStencilView()
{
	ResultInfo result;
	HRESULT hr;

	//Describe our Depth/Stencil Buffer
	D3D11_TEXTURE2D_DESC depthStencilDesc;

	depthStencilDesc.Width     = Width;
	depthStencilDesc.Height    = Height;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format    = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count   = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage          = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags      = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0; 
	depthStencilDesc.MiscFlags      = 0;

	//Create the Depth/Stencil View
	hr = d3d11Device->CreateTexture2D(&depthStencilDesc, NULL, &depthStencilBuffer);
	if(FAILED(hr))
	{
		result.failed(this,"Failed to create depthStencilBuffer");
		return result;
	}

	hr = d3d11Device->CreateDepthStencilView(depthStencilBuffer, NULL, &depthStencilView);

	if(FAILED(hr)) result.failed(this,"Failed to create DepthStencilView");
	
	return result;
}
ResultInfo RenderingDevice::setRenderTargets()
{
	ResultInfo result;
	//Set our Render Target
	d3d11DevCon->OMSetRenderTargets( 1, &renderTargetView, depthStencilView );

	return result;
}
ResultInfo RenderingDevice::createDeferredContexts()
{
	ResultInfo result;
	HRESULT hr;

	if(numDeferredContexts > 0)
	{
		deferredContextArr = new ID3D11DeviceContext*[numDeferredContexts];
		for(int i = 0; i < numDeferredContexts; i++)
		{
			hr = d3d11Device->CreateDeferredContext(0,&deferredContextArr[i]);
			if(FAILED(hr))
			{
				result.failed(this,("Failed to create DeferredContext #"+toStr(i)));
				return result;
			}
		}
	}
	return result;
}
ResultInfo RenderingDevice::createAllShaders()
{
	ResultInfo result;

	result = createVShader(L"Resources/FX/Effects.fx",VS);
	if(!result.ok()) 
	{
		result.extendPath(this);
		return result;
	}

	result = createPShader(L"Resources/FX/Effects.fx",PS);
	if(!result.ok()) result.extendPath(this);

	return result;
}
ResultInfo RenderingDevice::createVShader(std::wstring path, ID3D11VertexShader* VS)
{
	ResultInfo result;
	HRESULT hr;

	//compile Vertex shader
	hr = D3DX11CompileFromFile(path.c_str(), 0, 0, "VS", "vs_5_0", 0, 0, 0, &VS_Buffer, 0, 0);
	
	if(FAILED(hr)) 
	{
		result.failed(this,"Failed to compile Vertex Shader");
		return result;
	}
	
	//Create Vertex Shader
	hr = d3d11Device->CreateVertexShader(VS_Buffer->GetBufferPointer(), VS_Buffer->GetBufferSize(), NULL, &VS);

	if(FAILED(hr)) 
	{
		printf("failed to create vertex shader\n");
		result.failed(this,"Failed to create Vertex Shader");
	}

	return result;
}
ResultInfo RenderingDevice::createPShader(std::wstring path, ID3D11PixelShader* PS)
{
	ResultInfo result;
	HRESULT hr;

	//compile Pixel Shader
	hr = D3DX11CompileFromFile(path.c_str(), 0, 0, "PS", "ps_5_0", 0, 0, 0, &PS_Buffer, 0, 0);
	if(FAILED(hr))
	{
		result.failed(this,"Failed to compile Pixel Shader");
		return result;
	}
	hr = d3d11Device->CreatePixelShader(PS_Buffer->GetBufferPointer(), PS_Buffer->GetBufferSize(), NULL, &PS);
	if(FAILED(hr)) 
	{
		printf("failed to create pixel shader\n");
		result.failed(this,"Failed to create Pixel Shader");
	}

	return result;
}
ResultInfo RenderingDevice::createIndexBuffer()
{
	ResultInfo result;
	HRESULT hr;

	D3D11_BUFFER_DESC indexBufferDesc;
	ZeroMemory( &indexBufferDesc, sizeof(indexBufferDesc) );

	indexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	indexBufferDesc.ByteWidth = sizeof(DWORD) * maxIndices;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	indexBufferDesc.MiscFlags = 0;

	hr = d3d11Device->CreateBuffer(&indexBufferDesc, NULL, &indexStreamBuff);

	if(FAILED(hr)) result.failed(this,"Failed to create Index Buffer");

	return result;
}
ResultInfo RenderingDevice::createStreamBuffers()
{
	ResultInfo result;
	HRESULT hr;

	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory( &vertexBufferDesc, sizeof(vertexBufferDesc) );

	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof( GeomStr ) * maxVertices;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;

	hr = d3d11Device->CreateBuffer( &vertexBufferDesc, NULL, &geomStreamBuff);
	if(FAILED(hr))
	{
		result.failed(this,"Failed to create Geometry Stream Buffer");
		return result;
	}


	vertexBufferDesc.ByteWidth = sizeof( TextStr ) * maxVertices;
	hr = d3d11Device->CreateBuffer( &vertexBufferDesc, NULL, &textCoordStreamBuff);

	if(FAILED(hr)) result.failed(this,"Failed to create Text Coordinate Stream Buffer");

	return result;
}
ResultInfo RenderingDevice::createInputLayouts()
{
	ResultInfo result;
	HRESULT hr;

	hr = d3d11Device->CreateInputLayout( defaultLayout, defaultInputLayoutNumElements, VS_Buffer->GetBufferPointer(), 
		VS_Buffer->GetBufferSize(), &defaultInputLayout );
	if(FAILED(hr)) result.failed(this,"Failed to create Input Layout");
	return result;
}
void RenderingDevice::setViewPort()
{
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = Width;
	viewport.Height = Height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	//Set the Viewport
	d3d11DevCon->RSSetViewports(1, &viewport);
}
ResultInfo RenderingDevice::createPerFrameCBuffer()
{
	ResultInfo result;

	return result;
}
ResultInfo RenderingDevice::createPerObjectCBuffer()
{
	ResultInfo result;
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
	if(FAILED(hr)) result.failed(this,"Failed to create perObjectCBuffer");

	return result;
}
ResultInfo RenderingDevice::createTextureSamplerStates()
{
	ResultInfo result;
	HRESULT hr;

	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory( &sampDesc, sizeof(sampDesc) );
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sampDesc.MinLOD = 0;
    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

	//Create the Sample State
	hr = d3d11Device->CreateSamplerState( &sampDesc, &defaultTextSamplerState );
	if(FAILED(hr)) result.failed(this,"Failed to create texture sampler state");

	return result;
}
ResultInfo RenderingDevice::createBlendStates()
{
	ResultInfo result;

	return result;
}
ResultInfo RenderingDevice::createRasterizerStates()
{
	ResultInfo result;
	HRESULT hr;

	D3D11_RASTERIZER_DESC cmdesc;
	ZeroMemory(&cmdesc, sizeof(D3D11_RASTERIZER_DESC));
    
	cmdesc.FillMode = D3D11_FILL_SOLID;
	cmdesc.CullMode = D3D11_CULL_NONE;
    
	hr = d3d11Device->CreateRasterizerState(&cmdesc, &backFaceCullState);
	if(FAILED(hr)) result.failed(this,"Failed to create rasterizer state");

	return result;
}
ID3D11Device* RenderingDevice::getD3DDevice()
{
	return d3d11Device;
}
