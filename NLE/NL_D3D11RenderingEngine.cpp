#include "NL_D3D11RenderingEngine.h"
#include "NL_ThreadLocal.h"
#include "NL_EngineServices.h"
#include "NL_D3D11Utility.h"
#include "NL_SharedData.h"
#include "NL_IWindowManager.h"

#include <imgui.h>
#include "imgui_impl_dx11.h"

#include <Windows.h>
#include <d3d11.h>

namespace NLE
{
	namespace GRAPHICS
	{
		D3D11RenderingEngine::D3D11RenderingEngine(EngineServices& eServices) :
			_eServices(eServices)
		{
		}

		D3D11RenderingEngine::~D3D11RenderingEngine()
		{
		}

		bool D3D11RenderingEngine::initialize(IWindowManager& windowManager)
		{
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

			auto screenSize = windowManager.getClientSize();

			if (!D3D11Utility::createDeviceAndSwapChain(
				(HWND)windowManager.getWindowHandle(),
				screenSize.width,
				screenSize.height,
				windowManager.getFullScreen(),
				_d3dDevice,
				_swapChain,
				_deviceContext))
				return false;

			if (!D3D11Utility::createBackBufferRenderTargetView(_d3dDevice, _swapChain, _backBufferRenderTargetView))
				return false;
			/*if (!D3D11Utility::createBlendStates(_d3dDevice, false, false, 1, false, _noBlendState))
				return false;*/
			if (!D3D11Utility::createDepthStencilView(_d3dDevice, screenSize.width, screenSize.height, _depthStencilView))
				return false;

			_deviceContext->OMSetRenderTargets(1, &_backBufferRenderTargetView, _depthStencilView);
			//if (!D3D11Utility::loadVertexShader(_d3dDevice, L"Forward_VS.hlsl", _vertexShader))
			//	return false;
			/*if (!D3D11Utility::createInputLayout(_d3dDevice, forwardPosNormTextDesc, ARRAYSIZE(forwardPosNormTextDesc), _vertexShader, _inputLayout))
				return false;
			if (!D3D11Utility::createRasterizerState(_d3dDevice, D3D11_CULL_BACK, D3D11_FILL_SOLID, _backFaceCull))
				return false;
			if (!D3D11Utility::createRasterizerState(_d3dDevice, D3D11_CULL_FRONT, D3D11_FILL_SOLID, _frontFaceCull))
				return false;
			if (!D3D11Utility::createTextureSamplerState(_d3dDevice, _textureSamplerState))
				return false;
			//if (!D3D11Utility::loadPixelShader(_d3dDevice, L"Forward_PS.hlsl", _pixelShader))
			//	return false;

			float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };

			
			_deviceContext->OMSetBlendState(_noBlendState, blendFactor, 0xffffffff);
			//_deviceContext->VSSetShader(_vertexShader.apiVertexShader, nullptr, 0);
			//_deviceContext->PSSetShader(_pixelShader.apiPixelShader, nullptr, 0);
			_deviceContext->IASetInputLayout(_inputLayout);
			D3D11Utility::setViewPort(_deviceContext, (float)screenResolution.width, (float)screenResolution.height);
			_deviceContext->PSSetSamplers(0, 1, &_textureSamplerState);
			_deviceContext->RSSetState(_backFaceCull);

			/*RESOURCES::TransformationBuff transformBuff;
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
				return false;*/

			ImGui_ImplDX11_Init(windowManager.getWindowHandle(), _d3dDevice, _deviceContext);


			return true;
		}

		void D3D11RenderingEngine::update(SystemServices* sServices, double deltaT)
		{
			NLE::TLS::PerformanceTimer::reference timer = NLE::TLS::performanceTimer.local();
			timer.deltaT();

			bool show_test_window = true;
			bool show_another_window = false;
			ImVec4 clear_col = ImColor(114, 144, 154);

			ImGui_ImplDX11_NewFrame();

			// 1. Show a simple window
			// Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets appears in a window automatically called "Debug"
			{
				static float f = 0.0f;
				ImGui::Text("Hello, world!");
				ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
				ImGui::ColorEdit3("clear color", (float*)&clear_col);
				if (ImGui::Button("Test Window")) show_test_window ^= 1;
				if (ImGui::Button("Another Window")) show_another_window ^= 1;
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			}

			// 2. Show another simple window, this time using an explicit Begin/End pair
			if (show_another_window)
			{
				ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_FirstUseEver);
				ImGui::Begin("Another Window", &show_another_window);
				ImGui::Text("Hello");
				ImGui::End();
			}

			// 3. Show the ImGui test window. Most of the sample code is in ImGui::ShowTestWindow()
			if (show_test_window)
			{
				ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);     // Normally user code doesn't need/want to call it because positions are saved in .ini file anyway. Here we just want to make the demo initial state a bit more friendly!
				ImGui::ShowTestWindow(&show_test_window);
			}



			_deviceContext->ClearRenderTargetView(_backBufferRenderTargetView, (float*)&clear_col);
			ImGui::Render();
			//auto* drawData = ImGui::GetDrawData();
			_swapChain->Present(0, 0);
			
			DATA::SharedData& data = _eServices.data->getData();
			data.sysExecutionTimes.set(RENDERING_ENGINE, timer.deltaT());
		}
	}
}
