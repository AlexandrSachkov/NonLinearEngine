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

#ifndef NL_D3D11_UTILITY_H_
#define NL_D3D11_UTILITY_H_

#include "NL_D3D11RenderingResources.h"


#include <string>
#include <cstdint>

namespace NLE
{
	namespace GRAPHICS
	{
		class D3D11Utility
		{
		public:
			static bool createDeviceAndSwapChain(
				HWND windowHandle, 
				uint_fast32_t screenWidth, 
				uint_fast32_t screenHeight,
				bool fullScreen,
				ID3D11Device*& device,
				IDXGISwapChain*& swapChain,
				ID3D11DeviceContext*& deviceContext
				);
			
			static bool createBackBufferRenderTargetView(
				ID3D11Device* device, 
				IDXGISwapChain* swapChain, 
				ID3D11RenderTargetView*& renderTargetView
				);

			static bool createBlendStates(
				ID3D11Device* device,
				bool enableBlend, 
				bool enableIndependentBlending, 
				uint_fast32_t numRenderTargets,
				bool enableAlphaToCoverage, 
				ID3D11BlendState*& blendState
				);

			template<class T>
			static bool createBuffer(
				ID3D11Device* device,
				D3D11_BIND_FLAG bindFlag,
				D3D11_USAGE usage,
				T data[],
				size_t dataLength,
				RESOURCES::Buffer& buffer
				);

			static bool createRenderTargetViews(
				ID3D11Device* device,
				uint_fast32_t numViews,
				uint_fast32_t width,
				uint_fast32_t height,
				ID3D11RenderTargetView*& renderTargetViews
				);

			static bool createDepthStencilView(
				ID3D11Device* device,
				uint_fast32_t width,
				uint_fast32_t height,
				ID3D11DepthStencilView*& depthStencilView
				);
			
			static bool createShaderResourceViewFromTexture2D(
				ID3D11Device* device, 
				ID3D11Texture2D* texture, 
				ID3D11ShaderResourceView*& resourceView
				);
			
			static bool createTexture2D(
				ID3D11Device* device,
				uint_fast32_t width,
				uint_fast32_t height,
				bool generateMipMaps,
				uint_fast32_t MSAALevel,
				D3D11_USAGE usage,
				D3D11_BIND_FLAG bindFlag,
				void* data,
				uint_fast32_t memPitch,
				ID3D11Texture2D*& texture
				);

			static bool createInputLayout(
				ID3D11Device* device, 
				D3D11_INPUT_ELEMENT_DESC ilDesc[],
				uint_fast32_t size,
				RESOURCES::VertexShader& vShader, 
				ID3D11InputLayout*& inputLayout
				);

			static bool createTextureSamplerState(ID3D11Device* device, ID3D11SamplerState*& samplerState);

			static bool createRasterizerState(
				ID3D11Device* device, 
				D3D11_CULL_MODE cullMode, 
				D3D11_FILL_MODE fillMode, 
				ID3D11RasterizerState*& rasterizerState
				);
				
			static bool loadVertexShader(ID3D11Device* device, std::wstring path, RESOURCES::VertexShader& vertexShader);
			static bool loadPixelShader(ID3D11Device* device, std::wstring path, RESOURCES::PixelShader& pixelShader);
			
			static void setFullscreen(IDXGISwapChain*& swapChain, bool fullScreen);

			static void setViewPort(
				ID3D11DeviceContext*& deviceContext, 
				uint_fast32_t numViewports, 
				float x, 
				float y, 
				float width, 
				float height, 
				float minDepth, 
				float maxDepth
				);

			static void setViewPort(
				ID3D11DeviceContext*& deviceContext, 
				float screenWidth,
				float screenHeight
				);

			static void updateBuffer(
				ID3D11DeviceContext*& deviceContext, 
				RESOURCES::Buffer& buffer, 
				void* data, 
				size_t dataSize
				);

			private:
				static bool compileBlobFromFile(
					std::wstring path,
					LPCSTR entryPoint,
					LPCSTR profile,
					ID3DBlob*& blob
					);

				static bool loadBlobFromFile(std::wstring path, ID3DBlob*& blob);
		};
	}
}

#include "NL_D3D11Utility.inl"

#endif