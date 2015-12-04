#ifndef NL_RENDERER_H_
#define NL_RENDERER_H_

#include "NL_IRenderer.h"
#include "NLCore\NL_System.h"
#include "NLCore\NL_SContainer.h"
#include "NLCore\NL_Thread.h"

#include <DirectXMath.h>
#include "tbb\atomic.h"
#include "tbb\spin_mutex.h"

#include <functional>
#include <thread>

namespace NLE
{
	namespace Core
	{
		class IEngine;
		class ISystem;
	}

	namespace GRAPHICS
	{
		class RenderingEngine;
		class Camera;
		class Renderer : public Core::System, public IRenderer
		{
		public:
			Renderer();
			~Renderer();

			bool initialize(Core::IEngine& engine);
			void release();

			bool initialized();
			bool isRunning();

			void setWindowHandle(void* handle);
			void setScreenDimensions(uint_fast32_t width, uint_fast32_t height);
			void setFullscreen(bool fullscreen);
			void stop();

			std::function<void()> const& getExecutionProcedure();
			Core::ISystem& getInterface();
			ID3D11Device* getDevice();

		private:
			void computeViewProjection();
			float toRadians(float degrees);
			void setViewProjection(DirectX::XMMATRIX& viewProjection);
			DirectX::XMMATRIX getViewProjection();
			void setEye(DirectX::XMVECTOR& eye);
			DirectX::XMVECTOR getEye();

			bool _initialized;
			tbb::atomic<bool> _running;
			std::function<void()> _procedure;

			Core::Thread _renderingThread;
			std::unique_ptr<RenderingEngine> _renderingEngine;
			std::unique_ptr<Camera> _camera;

			NLE::Core::Data::SContainer<char>* _cameraCommands;
			NLE::Core::Data::SContainer<double>* _cursorCoords;
			NLE::Core::Data::SContainer<double>* _scrollOffset;

			uint_fast32_t _screenWidth;
			uint_fast32_t _screenHeight;

			bool _firstCameraUpdate;
			tbb::spin_mutex _viewProjectionLock;
			tbb::spin_mutex _eyeLock;

			std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::nanoseconds> _previousTime;
			float _lastX;
			float _lastY;
			bool _firstMouse;

			DirectX::XMMATRIX* _viewProjection;
			DirectX::XMVECTOR* _eye;

			float _lastCursorX;
			float _lastCursorY;
		};
	}
}

#endif