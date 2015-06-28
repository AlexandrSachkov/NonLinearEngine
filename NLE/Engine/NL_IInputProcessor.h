#ifndef NL_I_INPUT_PROCESSOR_H_
#define NL_I_INPUT_PROCESSOR_H_

#include "NLCore\NL_ISystem.h"
#include <functional>

namespace NLE
{
	namespace INPUT
	{
		struct Event;
	}

	class IInputProcessor : public Core::ISystem
	{
	public:
		virtual void attachEventPollingOperation(std::function<void()> const& operation) = 0;
		virtual void processEvent(INPUT::Event& event) = 0;
	};
}

#endif