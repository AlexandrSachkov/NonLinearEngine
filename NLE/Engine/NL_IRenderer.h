#ifndef NL_I_RENDERER_H_
#define NL_I_RENDERER_H_

#include "NLCore\NL_ISystem.h"
#include "NL_RenderingResources.h"
#include <cstdint>

struct ID3D11Device;
namespace NLE
{
	namespace GRAPHICS
	{
		namespace COMMANDS
		{
			enum CAMERA
			{
				FORWARD,
				REVERSE,
				LEFT,
				RIGHT,
				NUM_COMMANDS // used only to count commands
			};
		}
		
		class IRenderer : public Core::ISystem
		{
		public:
			virtual void setWindowHandle(void* handle) = 0;
			virtual void setScreenDimensions(uint_fast32_t width, uint_fast32_t height) = 0;
			virtual void setFullscreen(bool fullscreen) = 0;
			virtual void stop() = 0;
			virtual ID3D11Device* getDevice() = 0;

			virtual void addStaticRenderable(RESOURCES::Renderable& renderable) = 0;
			virtual void addLight(RESOURCES::Light& light) = 0;
		};
	}
}

#endif