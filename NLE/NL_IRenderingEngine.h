#ifndef NL_I_RENDERING_ENGINE_H_
#define NL_I_RENDERING_ENGINE_H_

#include "NL_CommonTypes.h"
#include <cstdint>
#include <string>

struct ID3D11Device;
namespace NLE
{
	namespace GRAPHICS
	{
		class IRenderingEngine
		{
		public:
			virtual void setWindowTitle(std::wstring title) = 0;
			virtual void setResolution(Size2D resolution) = 0;
			virtual void setFullscreen(bool fullscreen) = 0;
		};
	}
}

#endif