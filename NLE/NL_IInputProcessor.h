#ifndef NL_I_INPUT_PROCESSOR_H_
#define NL_I_INPUT_PROCESSOR_H_

#include "NL_InputEvents.h"

namespace NLE
{
	namespace INPUT
	{
		struct Event;
		class IInputProcessor
		{
		public:
			virtual void queueEvent(INPUT::Event& event) = 0;
			virtual void enableTextInput(bool enable) = 0;
			virtual void enableInputProcessing(bool enable) = 0;
		};
	}
}

#endif