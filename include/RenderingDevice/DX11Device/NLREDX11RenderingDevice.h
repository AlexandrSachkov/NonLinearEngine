#ifndef NLRE_DX11_RENDERING_DEVICE_
#define NLRE_DX11_RENDERING_DEVICE_

#include "stdafx.h"
#include <d3d11.h>

#include "RenderingDevice\NLREInputLayoutDescriptions.h"
#include "DDSTextureLoader.h"
#include "WICTextureLoader.h"

class NLREDX11RenderingDevice
{
public:
	NLREDX11RenderingDevice(HWND hwndVal, int widthVal, int heightVal);
	NLREDX11RenderingDevice(const NLREDX11RenderingDevice&);
	~NLREDX11RenderingDevice();

	bool createBackBufferRenderTargetView(NLRE_APIRenderTargetView* renderTargetView);
	template<class DataType> 
	bool createBuffer(
		NLRE_BIND_FLAG bindFlag, 
		NLRE_USAGE usage, 
		DataType dataArr[], 
		size_t arrayLength,
		NLRE_Buffer& buffer);

	bool createDepthStencilView(NLRE_APIDepthStencilView* depthStencilView);
	bool createInputLayout(NLRE_InputLayoutDesc ilDesc, NLRE_VertexShader vShader, NLRE_APIInputLayout* inputLayout);
	bool createRasterizerState(NLRE_CULL_MODE cullMode, NLRE_FILL_MODE fillMode, NLRE_APIRasterizerState* rasterizerState);
	bool createRenderTargetViews(unsigned int numViews, NLRE_APIRenderTargetView* renderTargetViewArr);
	bool createTextureSamplerState(NLRE_APISamplerState* samplerState);

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
	bool setRenderTargets(unsigned int numRenderTargets, NLRE_APIRenderTargetView* renderTargerViewArr, NLRE_APIDepthStencilView* depthStencilView);
	void setViewPort(int numViewports, int x, int y, int width, int height, float minDepth, float maxDepth);
	bool VSSetTextureSamplerState(unsigned int startSlot, unsigned int numStates, NLRE_APISamplerState* samplerState);
	bool PSSetTextureSamplerState(unsigned int startSlot, unsigned int numStates, NLRE_APISamplerState* samplerState);
	bool GSSetTextureSamplerState(unsigned int startSlot, unsigned int numStates, NLRE_APISamplerState* samplerState);
	//bool createBlendStates();
	void setRasterizerState(NLRE_APIRasterizerState* rasterizerState);
	void setInputLayout(NLRE_APIInputLayout* inputLayout);


private:
	bool initialize();
	void release();

	bool createDeviceAndSwapChain();
	bool loadBlobFromFile(std::wstring path, NLRE_ShaderBlob& blob);
	
	HWND _hwnd;
	int _screenWidth;
	int _screenHeight;
	
	IDXGISwapChain* SwapChain;
	ID3D11Device* d3d11Device;
	ID3D11DeviceContext* _d3d11DevCon;
};


#endif