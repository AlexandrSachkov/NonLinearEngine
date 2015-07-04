#ifndef NL_I_RENDERER_H_
#define NL_I_RENDERER_H_

#include "NLCore\NL_ISystem.h"
#include <functional>

namespace NLE
{
	namespace GRAPHICS
	{
		class IRenderer : public Core::ISystem
		{
		public:
			virtual void stop() = 0;
			virtual void attachMakeContextCurrent(std::function<void()> const& operation) = 0;
			virtual void attachSwapBuffers(std::function<void()> const& operation) = 0;
		};
	}
}

#endif