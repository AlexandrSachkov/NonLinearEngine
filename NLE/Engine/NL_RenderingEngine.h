#ifndef NL_RENDERING_ENGINE_H_
#define NL_RENDERING_ENGINE_H_

#include <Windows.h>
#include <d3d11.h>
#include <memory>
#include <cstdint>
#include <chrono>
#include <string>

namespace NLE
{
	namespace GRAPHICS
	{
		class D3D11Device;
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

			std::unique_ptr<D3D11Device> _device;
			HWND _hwnd;
			uint_fast32_t _screenWidth;
			uint_fast32_t _screenHeight;
			bool _fullscreen;

			ID3D11Device* _d3dDevice;
			IDXGISwapChain* _swapChain;
			ID3D11DeviceContext* _deviceContext;

			ID3D11RenderTargetView* _backBufferRenderTargetView;
		};
	}
}

#endif