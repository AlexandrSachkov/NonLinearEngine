#ifndef NL_I_INPUT_PROCESSOR_H_
#define NL_I_INPUT_PROCESSOR_H_

#include "NLCore\NL_ISystem.h"
#include <functional>

namespace NLE
{
	namespace INPUT
	{
		struct Event;

		class IInputProcessor : public Core::ISystem
		{
		public:
			virtual void attachPollEvents(std::function<void()> pollEvents) = 0;
			virtual void processEvent(INPUT::Event& event) = 0;

			virtual void enableTextInput(bool enable) = 0;
			virtual void enableInputProcessing(bool enable) = 0;
		};
	}
}

#endif