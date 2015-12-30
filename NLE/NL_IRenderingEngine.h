#ifndef NL_I_RENDERING_ENGINE_H_
#define NL_I_RENDERING_ENGINE_H_

#include "NL_ISystem.h"
#include <cstdint>

struct ID3D11Device;
namespace NLE
{
	namespace GRAPHICS
	{
		class IRenderingEngine : public Core::ISystem
		{
		public:
			virtual ID3D11Device* getDevice() = 0;
		};
	}
}

#endif