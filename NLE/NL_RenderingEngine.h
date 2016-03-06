#ifndef NL_RENDERING_ENGINE_H_
#define NL_RENDERING_ENGINE_H_

#include "NL_IRenderingEngine.h"
#include "NL_ISystem.h"
#include "NL_EngineServices.h"
#include "NL_Timer.h"
#include "NL_Thread.h"
#include "NL_CommonTypes.h"

#include "tbb/atomic.h"

#include <memory>
#include <cstdint>
#include <chrono>
#include <string>
#include <vector>

namespace NLE
{
	namespace WINDOW
	{
		class IWindowManager;
	}
	class WindowManager;
	namespace GRAPHICS
	{
		class Scene;
		class RenderingEngine : public IRenderingEngine, public ISystem
		{
		public:
			RenderingEngine(EngineServices& eServices);
			~RenderingEngine();

			bool initialize();
			void update(SystemServices& sServices, DataManager& data, double deltaT);

			void setWindowTitle(std::wstring title);
			void setResolution(Size2D resolution);
			void setFullscreen(bool fullscreen);

		private:	
			EngineServices& _eServices;
			WindowManager* _windowManager;
			Size2D _resolution;
			bool _fullscreen;
			bool _decorated;
		};
	}
}

#endif