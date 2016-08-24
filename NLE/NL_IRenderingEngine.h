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
		};

		class IRenderingEngine : public ISystem, public IRenderingEngine_SysService
		{
		public:
		};
	}
}

#endif