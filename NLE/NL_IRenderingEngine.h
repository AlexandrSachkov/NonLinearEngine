#ifndef NL_I_RENDERING_ENGINE_H_
#define NL_I_RENDERING_ENGINE_H_

#include "NL_ISystem.h"
#include <cstdint>
#include <string>

struct ID3D11Device;
namespace NLE
{
	namespace GRAPHICS
	{
		class IRenderingEngine : public Core::ISystem
		{
		public:
			virtual void setWindowTitle(std::wstring title) = 0;
		};
	}
}

#endif