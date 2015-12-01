#include "NL_RenderingEngine.h"
#include "NL_D3D11Utility.h"
#include "NL_GScene.h"

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

			if (!D3D11Utility::createDeviceAndSwapChain(_hwnd, _screenWidth, _screenHeight, _fullscreen, _d3dDevice, _swapChain, _deviceContext))
				return false;
			if (!D3D11Utility::createBackBufferRenderTargetView(_d3dDevice, _swapChain, _backBufferRenderTargetView))
				return false;
			if (!D3D11Utility::createBlendStates(_d3dDevice, false, false, 1, false, _noBlendState))
				return false;
			if (!D3D11Utility::createDepthStencilView(_d3dDevice, _screenWidth, _screenHeight, _depthStencilView))
				return false;
			if (!D3D11Utility::loadVertexShader(_d3dDevice, L"D:\\Repositories\\NonLinearEngine\\NLE\\Engine\\Shaders\\Forward_VS.hlsl", _vertexShader))
				return false;
			if (!D3D11Utility::createInputLayout(_d3dDevice, forwardPosNormTextDesc, ARRAYSIZE(forwardPosNormTextDesc), _vertexShader, _inputLayout))
				return false;
			if (!D3D11Utility::createRasterizerState(_d3dDevice, D3D11_CULL_BACK, D3D11_FILL_SOLID, _backFaceCull))
				return false;
			if (!D3D11Utility::createRasterizerState(_d3dDevice, D3D11_CULL_FRONT, D3D11_FILL_SOLID, _frontFaceCull))
				return false;
			if (!D3D11Utility::createTextureSamplerState(_d3dDevice, _textureSamplerState))
				return false;
			if (!D3D11Utility::loadPixelShader(_d3dDevice, L"D:\\Repositories\\NonLinearEngine\\NLE\\Engine\\Shaders\\Forward_PS.hlsl", _pixelShader))
				return false;

			float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };

			_deviceContext->OMSetRenderTargets(1, &_backBufferRenderTargetView, _depthStencilView);
			_deviceContext->OMSetBlendState(_noBlendState, blendFactor, 0xffffffff);
			_deviceContext->VSSetShader(_vertexShader.apiVertexShader, nullptr, 0);
			_deviceContext->PSSetShader(_pixelShader.apiPixelShader, nullptr, 0);
			_deviceContext->IASetInputLayout(_inputLayout);
			D3D11Utility::setViewPort(_deviceContext, (float)_screenWidth, (float)_screenHeight);
			_deviceContext->PSSetSamplers(0, 1, &_textureSamplerState);
			_deviceContext->RSSetState(_backFaceCull);

			RESOURCES::TransformationBuff transformBuff;
			if (!GRAPHICS::D3D11Utility::createBuffer<RESOURCES::TransformationBuff>(
				_d3dDevice,
				D3D11_BIND_CONSTANT_BUFFER,
				D3D11_USAGE_DYNAMIC,
				&transformBuff,
				1,
				_transformationBuff
				))
				return false;

			RESOURCES::EyeBuff eyeBuff;
			if (!GRAPHICS::D3D11Utility::createBuffer<RESOURCES::EyeBuff>(
				_d3dDevice,
				D3D11_BIND_CONSTANT_BUFFER,
				D3D11_USAGE_DYNAMIC,
				&eyeBuff,
				1,
				_eyeBuff
				))
				return false;

			_initialized = true;
			return true;
		}

		void RenderingEngine::release()
		{
			if (!_initialized)
				return;

			if(_swapChain)
				_swapChain->SetFullscreenState(FALSE, NULL);

			SAFE_RELEASE(_textureSamplerState);
			SAFE_RELEASE(_frontFaceCull);
			SAFE_RELEASE(_backFaceCull);
			SAFE_RELEASE(_inputLayout);
			SAFE_RELEASE(_depthStencilView);
			SAFE_RELEASE(_noBlendState);
			SAFE_RELEASE(_backBufferRenderTargetView);

			SAFE_RELEASE(_swapChain);
			SAFE_RELEASE(_deviceContext);
			SAFE_RELEASE(_d3dDevice);

			_initialized = false;
		}

		ID3D11Device* RenderingEngine::getDevice()
		{
			assert(_initialized);
			return _d3dDevice;
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

		void RenderingEngine::render(Scene* scene, DirectX::XMMATRIX& viewProjection, DirectX::XMVECTOR& eye)
		{
			//Clear our backbuffer to the updated color
			const float bgColor[] = { 0.4f, 0.4f, 0.4f, 1.0f };

			_deviceContext->ClearRenderTargetView(_backBufferRenderTargetView, bgColor);
			_deviceContext->ClearDepthStencilView(_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

			if (scene)
			{
				scene->recompileBuffers(_d3dDevice, _deviceContext);
				auto lightBuff = scene->getLightBuffer();
				_deviceContext->PSSetConstantBuffers(0, 1, &lightBuff.apiBuffer);

				RESOURCES::EyeBuff eyeBuff;
				DirectX::XMFLOAT4 eyeTemp;
				DirectX::XMStoreFloat4(&eyeTemp, eye);

				eyeBuff.eye = DirectX::XMFLOAT3(eyeTemp.x, eyeTemp.y, eyeTemp.z);
				D3D11Utility::updateBuffer(_deviceContext, _eyeBuff, &eyeBuff, sizeof(eyeBuff));
				_deviceContext->PSSetConstantBuffers(2, 1, &_transformationBuff.apiBuffer);

				for (auto renderable : scene->getStaticOpaqueRenderables())
				{
					if (renderable.mesh.geomBuffer.apiBuffer)
					{
						unsigned int stride = 0;
						_deviceContext->IASetVertexBuffers(0, 1, &(renderable.mesh.geomBuffer.apiBuffer), &(renderable.mesh.geomBuffer.elementSize), &stride);
					}
					if (renderable.mesh.indexBuffer.apiBuffer)
					{
						_deviceContext->IASetIndexBuffer(renderable.mesh.indexBuffer.apiBuffer, DXGI_FORMAT_R32_UINT, 0);
						_deviceContext->IASetPrimitiveTopology(renderable.mesh.primitiveTopology);
					}

					RESOURCES::TransformationBuff transformBuff;
					transformBuff.world = renderable.transformation.world;
					transformBuff.worldInverseTranspose = renderable.transformation.worldInverseTranspose;

					DirectX::XMMATRIX objWorld = DirectX::XMLoadFloat4x4(&renderable.transformation.world);
					DirectX::XMMATRIX WVP = objWorld * viewProjection;
					DirectX::XMStoreFloat4x4(&transformBuff.WVP, DirectX::XMMatrixTranspose(WVP));

					D3D11Utility::updateBuffer(_deviceContext, _transformationBuff, &transformBuff, sizeof(transformBuff));
					_deviceContext->VSSetConstantBuffers(0, 1, &_transformationBuff.apiBuffer);

					_deviceContext->PSSetConstantBuffers(1, 1, &renderable.material.materialBuffer.apiBuffer);
					if (renderable.material.diffuseTextView)
					{
						_deviceContext->PSSetShaderResources(0, 1, &renderable.material.diffuseTextView);
					}
					_deviceContext->DrawIndexed(renderable.mesh.indexBuffer.numberElements, 0, 0);
				}
			}


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