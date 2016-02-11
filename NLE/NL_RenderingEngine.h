#ifndef NL_RENDERING_ENGINE_H_
#define NL_RENDERING_ENGINE_H_

#include "NL_IRenderingEngine.h"
#include "NL_System.h"
#include "NL_RenderingResources.h"
#include "NL_Timer.h"
#include "NL_Thread.h"
#include "NL_SysInitializer.h"
#include "NL_CommonTypes.h"

#include "tbb/atomic.h"

#include <memory>
#include <cstdint>
#include <chrono>
#include <string>
#include <vector>

#include "gl\glew.h"

struct lua_State;
namespace NLE
{
	namespace Core
	{
		class IEngine;
		class ISystem;
		struct SysInitializer;
	}
	namespace IMPORTER
	{
		class AssetImporter;
	}
	namespace WINDOW
	{
		class IWindowManager;
	}
	class WindowManager;
	namespace GRAPHICS
	{
		struct Initializer : public Core::SysInitializer
		{
			Initializer() :
				screenSize(Size2D(0, 0)),
				fullscreen(false),
				decorated(true)
			{}
			Size2D screenSize;
			bool fullscreen;
			bool decorated;
		};

		class Scene;
		class RenderingEngine : public Core::System, public IRenderingEngine
		{
		public:
			RenderingEngine();
			~RenderingEngine();

			bool initialize(std::unique_ptr<Core::SysInitializer> const& initializer);
			void start();
			void stop();
			void release();
			bool initialized();
			std::function<void()> const& getExecutionProcedure();
			Core::ISystem& getInterface();

			void setWindowTitle(std::wstring title);

		private:
			void initOpengl();
			void releaseOpengl();
			void render();		

			bool _initialized;
			std::function<void()> _procedure;

			WindowManager* _windowManager;
			Initializer* _init;
			Timer _timer;
			tbb::atomic<bool> _firstRun;
			Core::Thread* _renderingThread;

			GLuint _renderProgram;
			GLuint _vertexArray;
		};
	}
}

#endif