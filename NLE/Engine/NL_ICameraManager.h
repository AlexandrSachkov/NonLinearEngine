#ifndef NL_I_CAMERA_MANAGER_H_
#define NL_I_CAMERA_MANAGER_H_

#include "NLCore\NL_ISystem.h"
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
		
		class ICameraManager : public Core::ISystem
		{
		public:
			virtual void setScreenDimensions(uint_fast32_t width, uint_fast32_t height) = 0;
		};
	}
}

#endif