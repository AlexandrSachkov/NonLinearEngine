#ifndef NL_I_CAMERA_CONTROLLER_H_
#define NL_I_CAMERA_CONTROLLER_H_

#include "NLCore\NL_ISystem.h"
#include <cstdint>

namespace NLE
{
	namespace CAMERA
	{
		enum COMMANDS
		{
			FORWARD,
			REVERSE,
			LEFT,
			RIGHT,
			NUM_COMMANDS // used only to count commands
		};

		class ICameraController : public Core::ISystem
		{
		public:
			virtual void setScreenDimensions(uint_fast32_t width, uint_fast32_t height) = 0;
		};
	}
}

#endif