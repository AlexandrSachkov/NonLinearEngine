#ifndef NLRE_DX11_RENDERING_DEVICE_
#define NLRE_DX11_RENDERING_DEVICE_

#include "NLREMain\stdafx.h"
#include <d3d11.h>
#include <d3dcompiler.h>

class NLREDX11RenderingDevice
{
public:
	NLREDX11RenderingDevice(HWND hwndVal, int widthVal, int heightVal);
	NLREDX11RenderingDevice(const NLREDX11RenderingDevice&);
	~NLREDX11RenderingDevice();

	bool createBackBufferRenderTargetView(NLRE_APIRenderTargetView*& renderTargetView);
	bool createBlendStates(bool enableBlend, bool enableIndependentBlending, unsigned int numRenderTargets, bool enableAlphaToCoverage, NLRE_APIBlendState*& blendState);
	template<class DataType> 
	bool createBuffer(
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
		bufferDesc.Usage = (D3D11_USAGE)usage;

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

		ID3D11Buffer* apiBuffer;
		hr = _d3d11Device->CreateBuffer(&bufferDesc, &subresData, &apiBuffer);

		if (FAILED(hr))
		{
			NLRE_Log::err(NLRE_Log::ErrorFlag::CRITICAL, "Failed to create Buffer Type: ", bindFlag, ", Usage: ", usage);
			return false;
		}

		buffer.apiBuffer = apiBuffer;
		buffer.bindFlag = bindFlag;
		buffer.usage = usage;
		buffer.elementSize = sizeof(DataType);
		buffer.numberElements = arrayLength;

		return true;
	}

	bool createDepthStencilView(NLRE_APIDepthStencilView*& depthStencilView);
	bool createInputLayout(NLRE_InputLayoutDesc& ilDesc, NLRE_VertexShader& vShader, NLRE_APIInputLayout*& inputLayout);
	bool createRasterizerState(NLRE_CULL_MODE cullMode, NLRE_FILL_MODE fillMode, NLRE_APIRasterizerState*& rasterizerState);
	bool createRenderTargetViews(unsigned int numViews, NLRE_APIRenderTargetView*& renderTargetViewArr);
	bool createTextureSamplerState(NLRE_APISamplerState*& samplerState);

	bool loadVertexShader(std::wstring path, NLRE_VertexShader& vertexShader);
	bool loadPixelShader(std::wstring path, NLRE_PixelShader& pixelShader);
	bool loadTexture(std::wstring path, NLRE_USAGE usage, NLRE_BIND_FLAG bindFlag, NLRE_APIResource* texture, NLRE_APIShaderResourceView* resourceView);

	void VSSetShaderResources(unsigned int startSlot, unsigned int numViews, NLRE_APIShaderResourceView* resourceViewArr);
	void PSSetShaderResources(unsigned int startSlot, unsigned int numViews, NLRE_APIShaderResourceView* resourceViewArr);
	void GSSetShaderResources(unsigned int startSlot, unsigned int numViews, NLRE_APIShaderResourceView* resourceViewArr);

	void setVertexShader(const NLRE_VertexShader& vertexShader);
	void setPixelShader(const NLRE_PixelShader& pixelShader);

	void VSSetConstantBuffer(unsigned int startSlot, unsigned int numBuffers, const NLRE_Buffer& buffer);
	void PSSetConstantBuffer(unsigned int startSlot, unsigned int numBuffers, const NLRE_Buffer& buffer);
	void GSSetConstantBuffer(unsigned int startSlot, unsigned int numBuffers, const NLRE_Buffer& buffer);

	void setVertexBuffer(const NLRE_Buffer& buffer, unsigned int slotNum);
	void setIndexBuffer(const NLRE_Buffer& buffer);

	void setBlendState(NLRE_APIBlendState* blendState, float blendFactor[]);
	void setInputLayout(NLRE_APIInputLayout* inputLayout);
	void setPrimitiveTopology(NLRE_PRIMITIVE_TOPOLOGY primitiveTopology);
	void setRasterizerState(NLRE_APIRasterizerState* rasterizerState);
	void setRenderTargets(unsigned int numRenderTargets, NLRE_APIRenderTargetView* renderTargerViewArr, NLRE_APIDepthStencilView* depthStencilView);
	void setViewPort(int numViewports, int x, int y, int width, int height, float minDepth, float maxDepth);
	void setViewPort();
	
	void VSSetTextureSamplerState(unsigned int startSlot, unsigned int numStates, NLRE_APISamplerState* samplerState);
	void PSSetTextureSamplerState(unsigned int startSlot, unsigned int numStates, NLRE_APISamplerState* samplerState);
	void GSSetTextureSamplerState(unsigned int startSlot, unsigned int numStates, NLRE_APISamplerState* samplerState);

	void clearRenderTargetView(NLRE_APIRenderTargetView* renderTargetView, float colorRGBA[]);
	void clearDepthStencilView(NLRE_APIDepthStencilView* depthStencilView);
	void drawIndexed(const NLRE_Buffer& indexBuffer);
	void draw(const NLRE_Buffer& vertexBuffer);
	void display();


private:
	bool initialize();
	void release();

	bool createDeviceAndSwapChain();
	bool loadBlobFromFile(std::wstring path, NLRE_ShaderBlob*& blob);
	
	HWND _hwnd;
	int _screenWidth;
	int _screenHeight;
	
	ID3D11Device* _d3d11Device;
	ID3D11DeviceContext* _d3d11DevCon;
	IDXGISwapChain* _swapChain;
};

#include "RenderingDeviceSrc\DX11Device\NLREDX11RenderingDevice.inl"
#endif