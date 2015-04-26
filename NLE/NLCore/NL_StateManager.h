#ifndef NL_STATE_MANAGER_H_
#define NL_STATE_MANAGER_H_

#include <cstdint>

namespace NLE
{
	namespace Core
	{
		class StateManager
		{
		public:
			virtual ~StateManager(){}

			virtual bool initialize() = 0;
			virtual void release() = 0;

			virtual void processRequests() = 0;
			virtual void distributeFrom(uint_fast8_t sysId) = 0;
			virtual void distributeTo(uint_fast8_t sysId) = 0;
		};
	}
}

#endif