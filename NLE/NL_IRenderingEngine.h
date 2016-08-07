#ifndef NL_I_RENDERING_ENGINE_H_
#define NL_I_RENDERING_ENGINE_H_

#include "NL_ISystem.h"
#include "NL_CommonTypes.h"
#include <cstdint>
#include <string>

namespace NLE
{
	namespace GRAPHICS
	{
		class IRenderingEngine_SysService
		{
		public:
			virtual void setWindowTitle(std::wstring title) = 0;
			virtual void setResolution(Size2D resolution) = 0;
			virtual void setFullscreen(bool fullscreen) = 0;
		};

		class IRenderingEngine : public ISystem, public IRenderingEngine_SysService
		{
		public:
			virtual bool initialize() = 0;
		};
	}
}

#endif