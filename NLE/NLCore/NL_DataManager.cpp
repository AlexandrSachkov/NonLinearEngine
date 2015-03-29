#include "NL_DataManager.h"
#include "NL_SysData.h"

namespace NLE
{
	namespace Core
	{
		DataManager::DataManager() :
			_sysData()
		{

		}

		DataManager::~DataManager()
		{

		}

		bool DataManager::initialize(uint_fast8_t numSystems)
		{
			_sharedData = std::make_unique<SysData>();
			for (uint_fast8_t i = 0; i < numSystems; i++)
			{
				_sysData.insert(std::make_pair<>(i, std::make_unique<SysData>()));
			}
			return true;
		}

		void DataManager::release()
		{

		}

		/*std::unique_ptr<SysData> const& DataManager::getDataHandle(uint_fast8_t sysId)
		{
			return nullptr;
		}*/


	}
}