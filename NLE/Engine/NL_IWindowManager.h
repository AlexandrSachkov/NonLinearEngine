#ifndef NL_I_WINDOW_MANAGER_H_
#define NL_I_WINDOW_MANAGER_H_

#include "NLCore/NL_ISystem.h"

namespace NLE
{
	namespace WINDOW
	{
		class IWindowManager : public Core::ISystem
		{
		public:
			virtual void makeContextCurrent(bool makeCurrent) = 0;
			virtual void enableVSync(bool enable) = 0;
			virtual void swapBuffers() = 0;
		};
	}

}

#endif