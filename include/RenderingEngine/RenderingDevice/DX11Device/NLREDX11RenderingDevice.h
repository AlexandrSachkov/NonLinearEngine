/*
-----------------------------------------------------------------------------
This source file is part of NLRE
(NonLinear Rendering Engine)
For the latest info, see https://github.com/AlexandrSachkov/NonLinearRenderingEngine

Copyright (c) 2014 NonLinear Rendering Engine Team

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/

#ifndef NLRE_DX11_RENDERING_DEVICE_
#define NLRE_DX11_RENDERING_DEVICE_

class NLREDX11RenderingDevice
{
public:
	NLREDX11RenderingDevice(NLEWindowReference hwndVal, int widthVal, int heightVal);
	~NLREDX11RenderingDevice();

	bool createBackBufferRenderTargetView(NLRE_APIRenderTargetView*& renderTargetView);
	bool createBlendStates(bool enableBlend, bool enableIndependentBlending, unsigned int numRenderTargets, bool enableAlphaToCoverage, NLRE_APIBlendState*& blendState);
	template<class DataType>
	bool createBuffer(
		NLRE_BIND_FLAG bindFlag,
		NLRE_USAGE usage,
		DataType dataArr[],
		size_t arrayLength,
		NLRE_Buffer& buffer);

	bool createDepthStencilView(NLRE_APIDepthStencilView*& depthStencilView);
	bool createInputLayout(NLRE_InputLayoutDesc& ilDesc, NLRE_VertexShader& vShader, NLRE_APIInputLayout*& inputLayout);
	bool createRasterizerState(NLRE_CULL_MODE cullMode, NLRE_FILL_MODE fillMode, NLRE_APIRasterizerState*& rasterizerState);
	bool createRenderTargetViews(unsigned int numViews, NLRE_APIRenderTargetView*& renderTargetViewArr);
	bool createShaderResourceViewFromTexture2D(NLRE_APITexture2D* texture, NLRE_APIShaderResourceView*& resourceView);
	bool createTexture2D(
		unsigned int width,
		unsigned int height,
		bool generateMipMaps,
		unsigned int MSAALevel,
		NLRE_USAGE usage,
		NLRE_BIND_FLAG bindFlag,
		void* data,
		unsigned int memPitch,
		NLRE_APITexture2D*& texture);

	bool createTextureSamplerState(NLRE_APISamplerState*& samplerState);

	bool loadVertexShader(std::wstring path, NLRE_VertexShader& vertexShader);
	bool loadPixelShader(std::wstring path, NLRE_PixelShader& pixelShader);

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
	void updateBuffer(NLRE_Buffer& buffer, void* data, unsigned int dataSize);
	
	void VSSetTextureSamplerState(unsigned int startSlot, unsigned int numStates, NLRE_APISamplerState* samplerState);
	void PSSetTextureSamplerState(unsigned int startSlot, unsigned int numStates, NLRE_APISamplerState* samplerState);
	void GSSetTextureSamplerState(unsigned int startSlot, unsigned int numStates, NLRE_APISamplerState* samplerState);

	void clearRenderTargetView(NLRE_APIRenderTargetView* renderTargetView, float colorRGBA[]);
	void clearDepthStencilView(NLRE_APIDepthStencilView* depthStencilView);
	void drawIndexed(const NLRE_Buffer& indexBuffer);
	void draw(const NLRE_Buffer& vertexBuffer);
	void display();

	ID3D11Device* getAPIDevice();
	ID3D11DeviceContext* getAPIPrimaryContext();
private:
	NLREDX11RenderingDevice(const NLREDX11RenderingDevice&);
	bool initialize();
	void release();

	bool createDeviceAndSwapChain();
	bool loadBlobFromFile(std::wstring path, NLRE_ShaderBlob*& blob);
	
	NLEWindowReference _hwnd;
	int _screenWidth;
	int _screenHeight;
	
	ID3D11Device* _d3d11Device;
	ID3D11DeviceContext* _d3d11DevCon;
	IDXGISwapChain* _swapChain;
};

#include "RenderingEngine\RenderingDevice\DX11Device\NLREDX11RenderingDevice.inl"
#endif