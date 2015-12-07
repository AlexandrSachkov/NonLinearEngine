#ifndef NL_I_RENDERING_ENGINE_H_
#define NL_I_RENDERING_ENGINE_H_

#include "NLCore\NL_ISystem.h"
#include <cstdint>

struct ID3D11Device;
namespace NLE
{
	namespace GRAPHICS
	{
		class IRenderingEngine : public Core::ISystem
		{
		public:
			virtual void setWindowHandle(void* handle) = 0;
			virtual void setScreenDimensions(uint_fast32_t width, uint_fast32_t height) = 0;
			virtual void setFullscreen(bool fullscreen) = 0;
			virtual ID3D11Device* getDevice() = 0;
		};
	}
}

#endif