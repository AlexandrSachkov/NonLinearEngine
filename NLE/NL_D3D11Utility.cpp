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


#include "NL_D3D11Utility.h"
//#include "NL_Console.h"

#include <d3dcompiler.h>
#include <assert.h>
#include "comdef.h"

namespace NLE
{
	namespace GRAPHICS
	{
		bool D3D11Utility::createDeviceAndSwapChain(
			HWND windowHandle,
			uint_fast32_t screenWidth,
			uint_fast32_t screenHeight,
			bool fullScreen,
			ID3D11Device*& device,
			IDXGISwapChain*& swapChain,
			ID3D11DeviceContext*& deviceContext
			)
		{
			HRESULT hr;

			//Describe our SwapChain Buffer
			DXGI_MODE_DESC bufferDesc;

			ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));

			bufferDesc.Width = screenWidth;
			bufferDesc.Height = screenHeight;
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
			swapChainDesc.BufferCount = 2;
			swapChainDesc.OutputWindow = windowHandle;
			swapChainDesc.Windowed = fullScreen == true ? FALSE : TRUE;
			swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
			swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

			UINT creationFlags = 0;
#if defined(_DEBUG) || defined(DEBUG)
			//creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

			//Create our SwapChain
			hr = D3D11CreateDeviceAndSwapChain(
				NULL,
				D3D_DRIVER_TYPE_HARDWARE,
				NULL,
				creationFlags,
				NULL,
				NULL,
				D3D11_SDK_VERSION,
				&swapChainDesc,
				&swapChain,
				&device,
				NULL,
				&deviceContext);

			if (FAILED(hr))
			{
				_com_error err(hr);
				//CONSOLE::out(CONSOLE::ERR, err.ErrorMessage());
				return false;
			}

			return true;
		}

		bool D3D11Utility::createBackBufferRenderTargetView(
			ID3D11Device* device,
			IDXGISwapChain* swapChain,
			ID3D11RenderTargetView*& renderTargetView
			)
		{
			HRESULT hr;

			//Create our BackBuffer
			ID3D11Texture2D* BackBuffer;
			hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer);

			if (FAILED(hr))
			{
				//CONSOLE::out(CONSOLE::ERR, L"Failed to get Back Buffer");
				return false;
			}

			//Create our Render Target
			hr = device->CreateRenderTargetView(BackBuffer, NULL, &renderTargetView);
			BackBuffer->Release();

			if (FAILED(hr))
			{
				//CONSOLE::out(CONSOLE::ERR, L"Failed to create Back Buffer Render Target View");
				return false;
			}

			return true;
		}

		bool D3D11Utility::createBlendStates(
			ID3D11Device* device,
			bool enableBlend,
			bool enableIndependentBlending,
			uint_fast32_t numRenderTargets,
			bool enableAlphaToCoverage,
			ID3D11BlendState*& blendState
			)
		{
			assert(numRenderTargets > 0 && numRenderTargets <= 8);

			HRESULT hr;
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
				for (uint_fast32_t i = 0; i < numRenderTargets; i++)
				{
					blendDesc.RenderTarget[i] = rtbd;
				}
			}
			else
			{
				blendDesc.RenderTarget[0] = rtbd;
			}


			hr = device->CreateBlendState(&blendDesc, &blendState);
			if (FAILED(hr))
			{
				//CONSOLE::out(CONSOLE::ERR, L"Failed to create blend state");
				return false;
			}
			return true;
		}

		bool D3D11Utility::createRenderTargetViews(
			ID3D11Device* device,
			uint_fast32_t numViews,
			uint_fast32_t width,
			uint_fast32_t height,
			ID3D11RenderTargetView*& renderTargetViews
			)
		{
			HRESULT hr;

			D3D11_TEXTURE2D_DESC textDesc;
			ZeroMemory(&textDesc, sizeof(textDesc));

			textDesc.Width = width;
			textDesc.Height = height;
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
			hr = device->CreateTexture2D(&textDesc, NULL, &buffer);
			if (FAILED(hr))
			{
				//CONSOLE::out(CONSOLE::ERR, L"Failed to create Render Target Buffer");
				return false;
			}

			//Create our Render Target
			hr = device->CreateRenderTargetView(buffer, NULL, &renderTargetViews);
			buffer->Release();

			if (FAILED(hr))
			{
				//CONSOLE::out(CONSOLE::ERR, L"Failed to create Back Buffer Render Target View");
				return false;
			}

			return true;
		}

		bool D3D11Utility::createDepthStencilView(
			ID3D11Device* device,
			uint_fast32_t width,
			uint_fast32_t height,
			ID3D11DepthStencilView*& depthStencilView
			)
		{
			HRESULT hr;

			//Describe our Depth/Stencil Buffer
			D3D11_TEXTURE2D_DESC depthStencilDesc;

			depthStencilDesc.Width = width;
			depthStencilDesc.Height = height;
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
			hr = device->CreateTexture2D(&depthStencilDesc, NULL, &buffer);
			if (FAILED(hr))
			{
				//CONSOLE::out(CONSOLE::ERR, L"Failed to create depthStencilBuffer");
				return false;
			}
			hr = device->CreateDepthStencilView(buffer, NULL, &depthStencilView);
			buffer->Release();

			if (FAILED(hr))
			{
				//CONSOLE::out(CONSOLE::ERR, L"Failed to create DepthStencilView");
				return false;
			}

			return true;
		}

		bool D3D11Utility::createShaderResourceViewFromTexture2D(
			ID3D11Device* device,
			ID3D11Texture2D* texture,
			ID3D11ShaderResourceView*& resourceView
			) 
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
			ZeroMemory(&srvDesc, sizeof(srvDesc));
			srvDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM; //changes based on the image format
			srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			srvDesc.Texture2D.MipLevels = -1;
			srvDesc.Texture2D.MostDetailedMip = 0;

			HRESULT hr;
			hr = device->CreateShaderResourceView(texture, &srvDesc, &resourceView);
			if (FAILED(hr))
			{
				//CONSOLE::out(CONSOLE::ERR, L"Failed to create Shader Resource View from Texture2D");
				return false;
			}
			return true;
		}

		bool D3D11Utility::createTexture2D(
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
			)
		{
			D3D11_TEXTURE2D_DESC textDesc;
			ZeroMemory(&textDesc, sizeof(textDesc));
			textDesc.Width = width;
			textDesc.Height = height;
			textDesc.MipLevels = generateMipMaps == true ? 0 : 1;
			textDesc.ArraySize = 1;
			textDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM; //needs to change based on texture format

			DXGI_SAMPLE_DESC sampleDesc;
			ZeroMemory(&sampleDesc, sizeof(sampleDesc));
			sampleDesc.Count = MSAALevel;
			sampleDesc.Quality = D3D11_STANDARD_MULTISAMPLE_PATTERN;

			textDesc.SampleDesc = sampleDesc;
			textDesc.Usage = usage;
			textDesc.BindFlags = bindFlag;
			textDesc.CPUAccessFlags = usage == D3D11_USAGE_DYNAMIC ? D3D11_CPU_ACCESS_WRITE : 0;
			textDesc.MiscFlags = 0;

			D3D11_SUBRESOURCE_DATA subresData;
			ZeroMemory(&subresData, sizeof(subresData));
			subresData.pSysMem = data;
			subresData.SysMemPitch = memPitch;

			HRESULT hr;
			hr = device->CreateTexture2D(&textDesc, &subresData, &texture);
			if (FAILED(hr))
			{
				//CONSOLE::out(CONSOLE::ERR, L"Failed to create texture");
				return false;
			}
			return true;
		}

		bool D3D11Utility::createInputLayout(
			ID3D11Device* device,
			D3D11_INPUT_ELEMENT_DESC ilDesc[],
			uint_fast32_t size,
			RESOURCES::VertexShader& vShader,
			ID3D11InputLayout*& inputLayout
			)
		{
			HRESULT hr;
			hr = device->CreateInputLayout(ilDesc, size, vShader.blob->GetBufferPointer(),
				vShader.blob->GetBufferSize(), &inputLayout);
			if (FAILED(hr))
			{
				//CONSOLE::out(CONSOLE::ERR, L"Failed to create Input Layout");
				return false;
			}
			return true;
		}

		bool D3D11Utility::createTextureSamplerState(ID3D11Device* device, ID3D11SamplerState*& samplerState)
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
			hr = device->CreateSamplerState(&sampDesc, &samplerState);
			if (FAILED(hr))
			{
				//CONSOLE::out(CONSOLE::ERR, L"Failed to create texture sampler state");
				return false;
			}

			return true;
		}



		bool D3D11Utility::createRasterizerState(
			ID3D11Device* device,
			D3D11_CULL_MODE cullMode,
			D3D11_FILL_MODE fillMode,
			ID3D11RasterizerState*& rasterizerState
			)
		{
			HRESULT hr;

			D3D11_RASTERIZER_DESC cmdesc;
			ZeroMemory(&cmdesc, sizeof(D3D11_RASTERIZER_DESC));

			cmdesc.CullMode = cullMode;
			cmdesc.FillMode = fillMode;

			hr = device->CreateRasterizerState(&cmdesc, &rasterizerState);
			if (FAILED(hr))
			{
				//CONSOLE::out(CONSOLE::ERR, L"Failed to create rasterizer state");
				return false;
			}

			return true;
		}

		bool D3D11Utility::compileBlobFromFile(std::wstring path, LPCSTR entryPoint, LPCSTR profile, ID3DBlob*& blob)
		{
			UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
			flags |= D3DCOMPILE_DEBUG;
#endif

			ID3DBlob* shaderBlob = nullptr;
			ID3DBlob* errorBlob = nullptr;
			HRESULT hr = D3DCompileFromFile(path.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
				entryPoint, profile,
				flags, 0, &blob, &errorBlob);
			if (FAILED(hr))
			{
				if (errorBlob)
				{
					OutputDebugStringA((char*)errorBlob->GetBufferPointer());
					errorBlob->Release();
					
					//CONSOLE::out(CONSOLE::ERR, L"Failed to compile blob.\n");
					return false;
				}			
			}
			return true;
		}

		bool D3D11Utility::loadBlobFromFile(std::wstring path, ID3DBlob*& blob)
		{
			HRESULT hr;

			hr = D3DReadFileToBlob(path.c_str(), &blob);
			if (FAILED(hr))
			{
				//CONSOLE::out(CONSOLE::ERR, L"Failed to load blob.\n");
				return false;
			}			
			return true;
		}


		bool D3D11Utility::loadVertexShader(ID3D11Device* device, std::wstring path, ID3D11VertexShader*& vertexShader)
		{
			HRESULT hr;
			//Load vertex shader from file
			std::wstring source(L".hlsl");
			std::wstring binary(L".cso");

			ID3DBlob* blob;
			bool result;
			if (path.rfind(source) != std::string::npos)
			{
				result = compileBlobFromFile(path, "VSMain", "vs_5_0", blob);
			}
			else if (path.rfind(binary) != std::string::npos)
			{
				result = loadBlobFromFile(path, blob);
			}
			else
			{
				//CONSOLE::out(CONSOLE::ERR, L"Invalid shader file extension: " + path);
				return false;
			}

			if (!result)
			{
				//CONSOLE::out(CONSOLE::ERR, L"Failed to load Vertex Shader: " + path);
				return false;
			}

			//Create Vertex Shader
			hr = device->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), NULL, &vertexShader);
			if (FAILED(hr))
			{
				//CONSOLE::out(CONSOLE::ERR, L"Failed to create Vertex Shader");
				return false;
			}

			return true;
		}

		bool D3D11Utility::loadPixelShader(ID3D11Device* device, std::wstring path, ID3D11PixelShader*& pixelShader)
		{
			HRESULT hr;

			//Load pixel shader from file
			std::wstring source(L".hlsl");
			std::wstring binary(L".cso");

			ID3DBlob* blob;
			bool result;
			if (path.rfind(source) != std::string::npos)
			{
				result = compileBlobFromFile(path, "PSMain", "ps_5_0", blob);
			}
			else if (path.rfind(binary) != std::string::npos)
			{
				result = loadBlobFromFile(path, blob);
			}
			else
			{
				//CONSOLE::out(CONSOLE::ERR, L"Invalid shader file extension: " + path);
				return false;
			}

			if (!result)
			{
				//CONSOLE::out(CONSOLE::ERR, L"Failed to load Pixel Shader: " + path);
				return false;
			}

			//Create Pixel Shader
			ID3D11PixelShader* ps = NULL;
			hr = device->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), NULL, &pixelShader);
			if (FAILED(hr))
			{
				//CONSOLE::out(CONSOLE::ERR, L"Failed to create Pixel Shader");
				return false;
			}

			return true;
		}

		void D3D11Utility::setFullscreen(IDXGISwapChain*& swapChain, bool fullScreen)
		{
			swapChain->SetFullscreenState(fullScreen, nullptr);
		}
	}
}


