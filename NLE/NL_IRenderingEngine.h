#ifndef NL_I_RENDERING_ENGINE_H_
#define NL_I_RENDERING_ENGINE_H_

#include "NL_ISystem.h"
#include "NL_CommonTypes.h"
#include <cstdint>
#include <string>
#include <functional>
#include <memory>

namespace NLE
{
	namespace GRAPHICS
	{
		class IRenderingEngine_SysService
		{
		};

		class IRenderingEngine : public ISystem, public IRenderingEngine_SysService
		{
		public:
			void attachGetUIRenderingData(std::function<void*()>);
		};

		typedef std::shared_ptr<IRenderingEngine> IRenderingEngineSP;
		typedef std::shared_ptr<IRenderingEngine_SysService> IRenderingEngine_SysServiceSP;
	}
}

#endif