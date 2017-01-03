#ifndef NL_I_INPUT_PROCESSOR_H_
#define NL_I_INPUT_PROCESSOR_H_

#include "NL_ISystem.h"
#include "NL_InputEvents.h"
#include <functional>
#include <memory>

namespace NLE
{
	namespace INPUT
	{
		class IInputProcessor_SysService
		{
		public:
			virtual void queueEvent(INPUT::Event& event) = 0;
			virtual void enableInputProcessing(bool enable) = 0;
			virtual void attachKeyAndCharCallback(std::function<void(INPUT::Event)> callback) = 0;
		};

		class IInputProcessor : public ISystem, public IInputProcessor_SysService
		{
		public:
		};

		typedef std::shared_ptr<IInputProcessor> IInputProcessorSP;
		typedef std::shared_ptr<IInputProcessor_SysService> IInputProcessor_SysServiceSP;
	}
}

#endif