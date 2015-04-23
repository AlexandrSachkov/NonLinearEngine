//#ifdef NL_DATA_DISTRIBUTOR_H_
#include "NL_DataDistributor.h"


namespace NLE
{
	namespace Core
	{
		DataDistributor::DataDistributor(uint_fast32_t initSize) :
			_dataContainers(),
			_size(initSize),
			_systemIds(),
			_additionPool(),
			_removalPool(),
			_additionQueue(_additionPool),
			_removalQueue(_removalPool)
		{
		}

		DataDistributor::~DataDistributor()
		{
		}

		std::unique_ptr<SharedDataContainer> const& DataDistributor::buildEndpoint(ExecutionDesc execDesc, AccessType preferredAccess)
		{
			uint_fast8_t sysId = execDesc.getSysId();
			_dataContainers.emplace(sysId, std::make_unique<SharedDataContainer>(
				this,
				execDesc.getExecutionType() == ExecutionType::ASYNC ? AccessType::READ_ONLY : preferredAccess,
				_size
				));
			_systemIds.push_back(sysId);
			return _dataContainers.at(sysId);
		}

		inline std::unique_ptr<SharedDataContainer> const& DataDistributor::getEndpoint(uint_fast8_t sysId)
		{
			return _dataContainers.at(sysId);
		}

		inline void DataDistributor::requestAdd(double data)
		{
			_additionQueue.push(data);
		}

		inline void DataDistributor::requestRemove(uint_fast32_t index)
		{
			_removalQueue.push(index);
		}


		void DataDistributor::distribute()
		{
			for (uint_fast8_t i = 0; i < _systemIds.size(); ++i)
			{
				auto& srcContainer = _dataContainers.at(_systemIds[i]);
				for (uint_fast8_t j = 0; j < _systemIds.size(); ++j)
				{
					if (i != j)
					{
						auto& destContainer = _dataContainers.at(_systemIds[j]);
						uint_fast32_t change;
						for (uint_fast32_t n = 0; n < srcContainer->getNumChanges(); ++n)
						{
							change = srcContainer->getChange(n);
							destContainer->distributor_modify(change, srcContainer->get(change));
						}
					}
				}
			}
		}
	}
}

//#endif