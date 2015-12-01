/*
-----------------------------------------------------------------------------
This source file is part of NLRE
(NonLinear Rendering Engine)
For the latest info, see https://github.com/AlexandrSachkov/NonLinearRenderingEngine

Copyright (c) 2015 Alexandr Sachkov

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

#ifdef NL_D3D11_UTILITY_H_

#include "NL_Console.h"

namespace NLE
{
	namespace GRAPHICS
	{
		template<class T>
		bool D3D11Utility::createBuffer(
			ID3D11Device* device,
			D3D11_BIND_FLAG bindFlag,
			D3D11_USAGE usage,
			T data[],
			size_t dataLength,
			RESOURCES::Buffer& buffer
			)
		{
			HRESULT hr;

			D3D11_BUFFER_DESC bufferDesc;
			ZeroMemory(&bufferDesc, sizeof(bufferDesc));


			bufferDesc.BindFlags = bindFlag;
			bufferDesc.Usage = usage;
			bufferDesc.CPUAccessFlags = usage == D3D11_USAGE_DYNAMIC ? D3D11_CPU_ACCESS_WRITE : 0;
			bufferDesc.ByteWidth = (uint_fast32_t)(sizeof(T)* dataLength);
			bufferDesc.MiscFlags = 0;

			D3D11_SUBRESOURCE_DATA subresData;
			ZeroMemory(&subresData, sizeof(subresData));
			subresData.pSysMem = data;

			ID3D11Buffer* apiBuffer;
			hr = device->CreateBuffer(&bufferDesc, &subresData, &apiBuffer);

			if (FAILED(hr))
			{
				CONSOLE::out(CONSOLE::ERR, "Failed to create Buffer Type:" + std::to_string(bindFlag) + ", Usage: " + std::to_string(usage));
				return false;
			}

			buffer.apiBuffer = apiBuffer;
			buffer.bindFlag = bindFlag;
			buffer.usage = usage;
			buffer.elementSize = sizeof(T);
			buffer.numberElements = (uint_fast32_t)dataLength;

			return true;
		}

		inline void D3D11Utility::setViewPort(
			ID3D11DeviceContext*& deviceContext,
			uint_fast32_t numViewports,
			float x,
			float y,
			float width,
			float height,
			float minDepth,
			float maxDepth
			)
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
			deviceContext->RSSetViewports(numViewports, &viewport);
		}

		inline void D3D11Utility::setViewPort(
			ID3D11DeviceContext*& deviceContext,
			float screenWidth,
			float screenHeight
			)
		{
			D3D11_VIEWPORT viewport;
			ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

			viewport.TopLeftX = 0;
			viewport.TopLeftY = 0;
			viewport.Width = screenWidth;
			viewport.Height = screenHeight;
			viewport.MinDepth = 0.0f;
			viewport.MaxDepth = 1.0f;

			//Set the Viewport
			deviceContext->RSSetViewports(1, &viewport);
		}

		inline void D3D11Utility::updateBuffer(
			ID3D11DeviceContext*& deviceContext,
			RESOURCES::Buffer& buffer,
			void* data,
			size_t dataSize
			)
		{
			D3D11_MAPPED_SUBRESOURCE mappedResource;
			ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

			deviceContext->Map(buffer.apiBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
			memcpy(mappedResource.pData, data, dataSize);
			deviceContext->Unmap(buffer.apiBuffer, 0);
		}
	}
}

#endif