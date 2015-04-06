#ifndef NL_SYS_STATE_H_
#define NL_SYS_STATE_H_


namespace NLE
{
	namespace Core
	{
		class StateManager;

		class SysState
		{
		public:
			virtual ~SysState(){}

			virtual bool initialize(uint_fast8_t sysId, 
				std::unique_ptr<StateManager> const& stateManager) = 0;
			virtual void release() = 0;
			virtual void update() = 0;
		};
	}
}


#endif