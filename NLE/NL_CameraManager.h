#ifndef NL_RENDERER_H_
#define NL_RENDERER_H_

#include "NL_ICameraManager.h"
#include "NL_System.h"
#include "NL_SysInitializer.h"
#include "NL_CommonTypes.h"

#include <DirectXMath.h>
#include "tbb\atomic.h"
#include "tbb\spin_mutex.h"

#include <functional>
#include <chrono>

namespace NLE
{
	namespace Core
	{
		class IEngine;
		class ISystem;
		struct SysInitializer;
	}

	namespace GRAPHICS
	{
		class RenderingEngine;
		class Camera;

		struct CameraManagerInitializer : public Core::SysInitializer
		{
			CameraManagerInitializer() :
				screenSize(Size2D(0, 0)) {}
			Size2D screenSize;
		};

		class CameraManager : public Core::System, public ICameraManager
		{
		public:
			CameraManager();
			~CameraManager();

			bool initialize(Core::IEngine& engine, std::unique_ptr<Core::SysInitializer> const& initializer);
			void start();
			void stop();
			void release();
			bool initialized();

			void setScreenDimensions(uint_fast32_t width, uint_fast32_t height);

			std::function<void()> const& getExecutionProcedure();
			Core::ISystem& getInterface();

		private:
			void computeViewProjection();
			float toRadians(float degrees);

			bool _initialized;
			std::function<void()> _procedure;
			std::unique_ptr<Camera> _camera;

			uint_fast32_t _screenWidth;
			uint_fast32_t _screenHeight;

			bool _firstCameraUpdate;

			std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::nanoseconds> _previousTime;
			float _lastX;
			float _lastY;
			bool _firstMouse;

			float _lastCursorX;
			float _lastCursorY;
		};
	}
}

#endif