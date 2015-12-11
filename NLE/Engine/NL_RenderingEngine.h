#ifndef NL_RENDERING_ENGINE_H_
#define NL_RENDERING_ENGINE_H_

#include "NL_IRenderingEngine.h"
#include "NLCore\NL_System.h"
#include "NLCore\NL_SContainer.h"
#include "NL_RenderingResources.h"

#include <Windows.h>
#include <d3d11.h>
#include <DirectXMath.h>

#include <memory>
#include <cstdint>
#include <chrono>
#include <string>
#include <vector>

struct lua_State;
namespace NLE
{
	namespace Core
	{
		class IEngine;
		class ISystem;
	}
	namespace IMPORTER
	{
		class AssetImporter;
	}
	namespace GRAPHICS
	{
		class Scene;
		class RenderingEngine : public Core::System, public IRenderingEngine
		{
		public:
			RenderingEngine();
			~RenderingEngine();

			bool initialize(Core::IEngine& engine);
			void release();
			bool initialized();
			std::function<void()> const& getExecutionProcedure();
			Core::ISystem& getInterface();

			void setWindowHandle(void* handle);
			void setScreenDimensions(uint_fast32_t width, uint_fast32_t height);
			void setFullscreen(bool fullscreen);
			ID3D11Device* getDevice();

		private:
			void render();		

			bool _initialized;
			std::function<void()> _procedure;
			uint_fast32_t _frameCount;
			std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::nanoseconds> _previousTime;

			NLE::Core::Data::SContainer<DirectX::XMFLOAT4X4>* _viewProjection;
			NLE::Core::Data::SContainer<DirectX::XMFLOAT4>* _eye;
			NLE::Core::Data::SContainer<double>* _fps;
			NLE::Core::Data::SContainer<DirectX::XMFLOAT4>* _canvasBgColor;

			HWND _hwnd;
			uint_fast32_t _screenWidth;
			uint_fast32_t _screenHeight;
			bool _fullscreen;

			ID3D11Device* _d3dDevice;
			IDXGISwapChain* _swapChain;
			ID3D11DeviceContext* _deviceContext;

			ID3D11RenderTargetView* _backBufferRenderTargetView;
			ID3D11BlendState* _noBlendState;
			ID3D11DepthStencilView* _depthStencilView;
			RESOURCES::VertexShader	_vertexShader;
			ID3D11InputLayout* _inputLayout;
			ID3D11RasterizerState* _backFaceCull;
			ID3D11RasterizerState* _frontFaceCull;
			ID3D11SamplerState*	_textureSamplerState;
			RESOURCES::PixelShader _pixelShader;

			RESOURCES::Buffer _transformationBuff;
			RESOURCES::Buffer _eyeBuff;
		};
	}
}

#endif