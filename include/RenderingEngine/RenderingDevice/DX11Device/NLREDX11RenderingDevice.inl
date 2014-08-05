/*
-----------------------------------------------------------------------------
This source file is part of NLRE
(NonLinear Rendering Engine)
For the latest info, see https://github.com/AlexandrSachkov/NonLinearRenderingEngine

Copyright (c) 2014 Alexandr Sachkov & NonLinear Engine Team

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

#ifdef NLRE_DX11_RENDERING_DEVICE_

#include <d3d11.h>
#include <d3dcompiler.h>

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
		NLRE_Log::err(NLRE_Log::ErrorFlag::CRITICAL, "Failed to create Buffer Type: %i%s%i", bindFlag, ", Usage: ", usage);
		return false;
	}

	buffer.apiBuffer = apiBuffer;
	buffer.bindFlag = bindFlag;
	buffer.usage = usage;
	buffer.elementSize = sizeof(DataType);
	buffer.numberElements = arrayLength;

	return true;
}

inline void NLREDX11RenderingDevice::setRenderTargets(
	unsigned int numRenderTargets,
	NLRE_APIRenderTargetView* renderTargerViewArr,
	NLRE_APIDepthStencilView* depthStencilView)
{
	_d3d11DevCon->OMSetRenderTargets(numRenderTargets, &renderTargerViewArr, depthStencilView);
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
	unsigned int stride = 0;
	_d3d11DevCon->IASetVertexBuffers(slotNum, 1, &(buffer.apiBuffer), &(buffer.elementSize), &stride);
}

inline void NLREDX11RenderingDevice::setIndexBuffer(const NLRE_Buffer& buffer)
{
	_d3d11DevCon->IASetIndexBuffer(buffer.apiBuffer, DXGI_FORMAT_R32_UINT, 0);
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

inline void NLREDX11RenderingDevice::setViewPort()
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
	_d3d11DevCon->RSSetViewports(1, &viewport);
}

inline void NLREDX11RenderingDevice::updateBuffer(NLRE_Buffer& buffer, void* data, unsigned int dataSize)
{
	if (buffer.usage == NLRE_USAGE_DYNAMIC)
	{
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));
		
		_d3d11DevCon->Map(buffer.apiBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		memcpy(mappedResource.pData, data, dataSize);
		_d3d11DevCon->Unmap(buffer.apiBuffer, 0);
	}
	else if (buffer.usage == NLRE_USAGE_DEFAULT)
	{
		//UpdateSubresource goes here
	}
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

inline void NLREDX11RenderingDevice::drawIndexed(const NLRE_Buffer& indexBuffer)
{
	_d3d11DevCon->DrawIndexed(indexBuffer.numberElements, 0, 0);
}

inline void NLREDX11RenderingDevice::draw(const NLRE_Buffer& vertexBuffer)
{
	_d3d11DevCon->Draw(vertexBuffer.numberElements, 0);
}

inline void NLREDX11RenderingDevice::display()
{
	_swapChain->Present(0, 0);
}

#endif