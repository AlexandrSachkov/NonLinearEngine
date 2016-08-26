#ifndef NL_RENDERING_ENGINE_H_
#define NL_RENDERING_ENGINE_H_

#include "NL_IRenderingEngine.h"
#include "NL_CommonTypes.h"

#include "tbb/atomic.h"

#include <memory>
#include <cstdint>
#include <chrono>
#include <string>
#include <vector>

namespace NLE
{
	class EngineServices;
	class IWindowManager;
	namespace GRAPHICS
	{
		class Scene;
		class RenderingEngine : public IRenderingEngine
		{
		public:
			RenderingEngine(EngineServices& eServices);
			~RenderingEngine();

			bool initialize();
			void update(SystemServices* sServices, double deltaT);
			void attachGetUIRenderingData(std::function<void*()>);

		private:	
			EngineServices& _eServices;
		};
	}
}

#endif