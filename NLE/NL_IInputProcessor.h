#ifndef NL_I_INPUT_PROCESSOR_H_
#define NL_I_INPUT_PROCESSOR_H_

#include "NL_ISystem.h"
#include "NL_InputEvents.h"

namespace NLE
{
	namespace INPUT
	{
		class IInputProcessor_SysService
		{
		public:
			virtual void queueEvent(INPUT::Event& event) = 0;
			virtual void enableTextInput(bool enable) = 0;
			virtual void enableInputProcessing(bool enable) = 0;
		};

		class IInputProcessor : public ISystem, public IInputProcessor_SysService
		{
		public:
			virtual bool initialize() = 0;
		};
	}
}

#endif