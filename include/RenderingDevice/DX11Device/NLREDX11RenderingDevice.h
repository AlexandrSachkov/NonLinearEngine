#ifndef NLRE_DX11_RENDERING_DEVICE_
#define NLRE_DX11_RENDERING_DEVICE_

#include "stdafx.h"
#include <d3d11.h>

#include "RenderingDevice\NLREInputLayoutDescriptions.h"
#include "DirectXTex.h"

struct cbPerObject
{
	NLE_FLOAT4X4 MVP;
};

class NLREDX11RenderingDevice
{
public:
	NLREDX11RenderingDevice(HWND hwndVal, int widthVal, int heightVal);
	NLREDX11RenderingDevice(const NLREDX11RenderingDevice&);
	~NLREDX11RenderingDevice();

	
	
	//====================================== Getter Functions ==========================================
	ID3D11Device* getD3DDevice();

private:
	bool initialize();
	void release();
	//====================================== Initialization Functions ==========================================
	bool initializeDirect3d11();
	bool createDeviceAndSwapChain();
	bool createRenderTargetView();
	bool createDepthStencilView();
	bool setRenderTargets();

	bool createAllResources();
	bool loadVertexShader(std::wstring path, NLRE_VertexShader& vertexShader);
	bool loadPixelShader(std::wstring path, NLRE_PixelShader& pixelShader);
	void setVertexShader(const NLRE_VertexShader& vertexShader);
	void setPixelShader(const NLRE_PixelShader& pixelShader);

	template<class DataType> bool createBuffer(
		NLRE_RenderStateId::BufferType buffType, 
		NLRE_RenderStateId::Usage usage, 
		DataType dataArr[], 
		size_t arrayLength,
		NLRE_Buffer& buffer);
	void setConstantBuffer(NLRE_RenderStateId::PipelineStage stage, const NLRE_Buffer& buffer, unsigned int slotNum);
	void setVertexBuffer(const NLRE_Buffer& buffer, unsigned int slotNum);
	void setIndexBuffer(const NLRE_Buffer& buffer);

	bool createInputLayout(NLRE_InputLayoutDesc ilDesc, NLRE_VertexShader vShader, NLRE_APIInputLayout* inputLayout);
	void setViewPort();
	bool createTextureSamplerStates();
	bool createBlendStates();
	bool createRasterizerStates();

	bool loadBlobFromFile(std::wstring path, NLRE_ShaderBlob& blob);
	//====================================== Pipeline Modification Functions ==========================================
	void setInputLayout(NLRE_APIInputLayout* inputLayout);


	
	
	HWND _hwnd;
	int _screenWidth;
	int _screenHeight;

	int numRenderingThreads;
	int numDeferredContexts;
	int maxIndices;
	int maxVertices;
	
	IDXGISwapChain* SwapChain;
	ID3D11Device* d3d11Device;
	ID3D11DeviceContext* _d3d11DevCon;
	ID3D11RenderTargetView* renderTargetView;
	ID3D11Texture2D* depthStencilBuffer;
	ID3D11DepthStencilView* depthStencilView;

	ID3D11SamplerState* defaultTextSamplerState;
	ID3D11RasterizerState* backFaceCullState;
};


#endif