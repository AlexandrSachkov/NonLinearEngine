#ifndef NL_STATE_MANAGER_H_
#define NL_STATE_MANAGER_H_

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

			virtual void distributeData() = 0;
		};
	}
}

#endif