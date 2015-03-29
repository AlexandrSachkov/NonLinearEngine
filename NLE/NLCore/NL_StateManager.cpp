#include "NL_StateManager.h"
#include "NL_SysState.h"

namespace NLE
{
	namespace Core
	{
		StateManager::StateManager() :
			_sysState()
		{

		}

		StateManager::~StateManager()
		{

		}

		bool StateManager::initialize(uint_fast8_t numSystems)
		{
			_sharedState = std::make_unique<SysState>();
			for (uint_fast8_t i = 0; i < numSystems; i++)
			{
				_sysState.insert(std::make_pair<>(i, std::make_unique<SysState>()));
			}
			return true;
		}

		void StateManager::release()
		{

		}

		std::unique_ptr<SysState> const& StateManager::getDataHandle(uint_fast8_t sysId)
		{
			return _sysState.at(sysId);
		}


	}
}