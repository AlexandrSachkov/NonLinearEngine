#ifndef NL_STATE_MANAGER_H_
#define NL_STATE_MANAGER_H_

#include <cstdint>
#include <memory>
#include <unordered_map>

namespace NLE
{
	namespace Core
	{
		class SysState;
		class StateManager
		{
		public:
			StateManager();
			~StateManager();

			bool initialize(uint_fast8_t numSystems);
			void release();

			//std::unique_ptr<SysState> const& getDataHandle(uint_fast8_t sysId);

		private:
			//std::unique_ptr<SysState> _sharedState;
			//std::unordered_map<uint_fast8_t, std::unique_ptr<SysState>> _sysState;

		};
	}
}

#endif