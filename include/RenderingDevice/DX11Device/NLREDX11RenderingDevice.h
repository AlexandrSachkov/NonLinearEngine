#ifndef NLRE_DX11_RENDERING_DEVICE_
#define NLRE_DX11_RENDERING_DEVICE_

#include "StreamSet.h"

struct cbPerObject
{
	XMFLOAT4X4  WVP;
};

class RenderingDevice : NLECoreDevice
{
public:
	RenderingDevice();
	RenderingDevice(const RenderingDevice&);
	~RenderingDevice();

	ResultInfo initialize(HWND hwndVal,int widthVal, int heightVal);
	void release();
	bool isInitialized();
	//====================================== Getter Functions ==========================================
	ID3D11Device* getD3DDevice();

private:
	
	//====================================== Initialization Functions ==========================================
	ResultInfo initializeDirect3d11();
	ResultInfo createDeviceAndSwapChain();
	ResultInfo createRenderTargetView();
	ResultInfo createDepthStencilView();
	ResultInfo setRenderTargets();
	ResultInfo createDeferredContexts();

	ResultInfo createAllResources();
	ResultInfo createAllShaders();
	ResultInfo createVShader(std::wstring path, ID3D11VertexShader* VS);
	ResultInfo createPShader(std::wstring path, ID3D11PixelShader* PS);
	ResultInfo createIndexBuffer();
	ResultInfo createStreamBuffers();
	ResultInfo createInputLayouts();
	void setViewPort();
	ResultInfo createPerFrameCBuffer();
	ResultInfo createPerObjectCBuffer();
	ResultInfo createTextureSamplerStates();
	ResultInfo createBlendStates();
	ResultInfo createRasterizerStates();

	//====================================== Pipeline Modification Functions ==========================================
	//void setShader(ID3D11DeviceContext* context);
	//void setInputLayout(ID3D11DeviceContext* context);


	
	


	bool initialized;
	HWND hwnd;
	int Width;
	int Height;

	int numRenderingThreads;
	int numDeferredContexts;
	int maxIndices;
	int maxVertices;
	
	IDXGISwapChain* SwapChain;
	ID3D11Device* d3d11Device;
	ID3D11DeviceContext* d3d11DevCon;
	ID3D11RenderTargetView* renderTargetView;
	ID3D11Texture2D* depthStencilBuffer;
	ID3D11DepthStencilView* depthStencilView;
	ID3D11DeviceContext** deferredContextArr;

	ID3D10Blob* VS_Buffer;
	ID3D10Blob* PS_Buffer;
	ID3D11VertexShader* VS;
	ID3D11PixelShader* PS;

	ID3D11Buffer* indexStreamBuff;
	ID3D11Buffer* geomStreamBuff;
	ID3D11Buffer* textCoordStreamBuff;

	ID3D11InputLayout* defaultInputLayout;
	ID3D11Buffer* perFrameCBuffer;
	ID3D11Buffer* perObjectCBuffer;
	ID3D11SamplerState* defaultTextSamplerState;
	ID3D11RasterizerState* backFaceCullState;

	static D3D11_INPUT_ELEMENT_DESC defaultLayout[];
	int defaultInputLayoutNumElements;
};


#endif