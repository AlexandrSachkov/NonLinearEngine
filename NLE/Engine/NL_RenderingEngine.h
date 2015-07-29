#ifndef NL_RENDERING_ENGINE_H_
#define NL_RENDERING_ENGINE_H_

#include "NL_RenderingResources.h"

#include <Windows.h>
#include <d3d11.h>
#include <memory>
#include <cstdint>
#include <chrono>
#include <string>
#include <vector>

namespace NLE
{
	namespace IMPORTER
	{
		class AssetImporter;
	}
	namespace GRAPHICS
	{
		class RenderingEngine
		{
		public:
			RenderingEngine();
			~RenderingEngine();

			bool initialize();
			void release();
			void render();

			void setWindowHandle(void* handle);
			void setScreenDimensions(uint_fast32_t width, uint_fast32_t height);
			void setFullscreen(bool fullscreen);
		private:
			bool _initialized;
			uint_fast32_t _frameCount;
			std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::nanoseconds> _previousTime;

			HWND _hwnd;
			uint_fast32_t _screenWidth;
			uint_fast32_t _screenHeight;
			bool _fullscreen;

			std::unique_ptr<IMPORTER::AssetImporter> _assetImporter;
			std::vector<RESOURCES::Renderable> _renderables;

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
		};
	}
}

#endif