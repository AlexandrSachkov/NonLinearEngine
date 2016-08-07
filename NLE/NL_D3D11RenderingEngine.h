#ifndef NL_D3D11_RenderingEngine_
#define NL_D3D11_RenderingEngine_

#include "NL_IRenderingEngine.h"
#include "NL_EngineServices.h"

namespace NLE
{
	namespace GRAPHICS
	{
		class D3D11RenderingEngine : public IRenderingEngine
		{
		public:
			D3D11RenderingEngine(EngineServices& eServices);
			~D3D11RenderingEngine();

		private:
		};
	}
}


#endif
