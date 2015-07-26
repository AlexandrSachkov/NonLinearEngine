#include "NL_RenderingEngine.h"
#include "NL_D3D11Device.h"

#include <cstdio>
#include <iostream>

namespace NLE
{
	namespace GRAPHICS
	{
		RenderingEngine::RenderingEngine() :
			_initialized(false),
			_frameCount(0),
			_previousTime(std::chrono::nanoseconds(0L)),
			_hwnd(nullptr),
			_screenWidth(0),
			_screenHeight(0),
			_fullscreen(true)
		{
			_device = std::make_unique<D3D11Device>();
			
			printf("Rendering Engine created\n");
		}

		RenderingEngine::~RenderingEngine()
		{
			release();
		}

		bool RenderingEngine::initialize()
		{
			assert(!_initialized && _hwnd && _screenWidth > 0 && _screenHeight > 0);

			D3D11_INPUT_ELEMENT_DESC forwardPosNormTanTextDesc[] = {
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "NORMAL", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TANGENT", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 36, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};

			D3D11_INPUT_ELEMENT_DESC forwardPosNormTextDesc[] = {
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "NORMAL", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};

			D3D11_INPUT_ELEMENT_DESC forwardPosTextDesc[] = {
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};

			D3D11_INPUT_ELEMENT_DESC forwardPosDesc[] = {
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};

			if (!_device->createDeviceAndSwapChain(_hwnd, _screenWidth, _screenHeight, _fullscreen, _d3dDevice, _swapChain, _deviceContext))
				return false;
			if (!_device->createBackBufferRenderTargetView(_d3dDevice, _swapChain, _backBufferRenderTargetView))
				return false;
			if (!_device->createBlendStates(_d3dDevice, false, false, 1, false, _noBlendState))
				return false;
			if (!_device->createDepthStencilView(_d3dDevice, _screenWidth, _screenHeight, _depthStencilView))
				return false;			
			if (!_device->loadVertexShader(_d3dDevice, L"D:\\Repositories\\NonLinearEngine\\NLE\\Engine\\Shaders\\Forward_Pos_VS.hlsl", _vertexShader))
				return false;			
			if (!_device->createInputLayout(_d3dDevice, forwardPosDesc, ARRAYSIZE(forwardPosDesc), _vertexShader, _inputLayout))
				return false;
			if (!_device->createRasterizerState(_d3dDevice, D3D11_CULL_BACK, D3D11_FILL_SOLID, _backFaceCull))
				return false;
			if (!_device->createRasterizerState(_d3dDevice, D3D11_CULL_FRONT, D3D11_FILL_SOLID, _frontFaceCull))
				return false;
			if (!_device->createTextureSamplerState(_d3dDevice, _textureSamplerState))
				return false;
			if (!_device->loadPixelShader(_d3dDevice, L"D:\\Repositories\\NonLinearEngine\\NLE\\Engine\\Shaders\\Forward_Pos_PS.hlsl", _pixelShader))
				return false;
			
			return true;
		}

		void RenderingEngine::release()
		{
			_swapChain->SetFullscreenState(FALSE, NULL);

			SAFE_RELEASE(_backBufferRenderTargetView);

			SAFE_RELEASE(_swapChain);
			SAFE_RELEASE(_deviceContext);
			SAFE_RELEASE(_d3dDevice);
		}

		void RenderingEngine::setWindowHandle(void* handle)
		{
			assert(!_initialized);
			_hwnd = (HWND)handle;
		}

		void RenderingEngine::setScreenDimensions(uint_fast32_t width, uint_fast32_t height)
		{
			assert(!_initialized);
			_screenWidth = width;
			_screenHeight = height;
		}

		void RenderingEngine::setFullscreen(bool fullscreen)
		{
			assert(!_initialized);
			_fullscreen = fullscreen;
		}

		void RenderingEngine::render()
		{
			//Clear our backbuffer to the updated color
			const float bgColor[] = { 0.0f, 1.0f, 0.0f, 1.0f };

			_deviceContext->ClearRenderTargetView(_backBufferRenderTargetView, bgColor);


			_swapChain->Present(0, 0);

			++_frameCount;
			if (_frameCount == 10000)
			{
				auto time = std::chrono::high_resolution_clock::now();
				auto diff = std::chrono::duration_cast<std::chrono::nanoseconds>(time - _previousTime).count();
				double fps = 1 / (diff / _frameCount * 0.000000001);
				std::cout << "FPS: " << fps << "\n";
				_previousTime = time;


				_frameCount = 0;
			}
		}
	}
}