#include "NL_SDistributor.h"
#include <cassert>

namespace NLE
{
	namespace Core
	{
		namespace Data
		{
			SDistributor::SDistributor(uint_fast32_t dataSize, uint_fast32_t queueSize) :
				_queueSize(queueSize)
			{
				_data.reserve(dataSize);
			}

			SDistributor::~SDistributor()
			{
				for (auto& i : _containers)
				{
					delete i.second;
				}
			}

			SContainer& SDistributor::buildEndpoint(uint_fast8_t sysId)
			{
				assert(_containers.count(sysId) == 0);
				_containers.emplace(sysId, new SContainer(_data.size(), _queueSize));
				return *_containers.at(sysId);
			}

			void SDistributor::distributeFrom(uint_fast8_t sysId)
			{
				if (_containers.count(sysId) > 0)
				{
					auto& src = *_containers.at(sysId);
					auto const& changes = src.getChanges();
					uint_fast32_t change;
					for (uint_fast32_t i = 0; i < changes.size(); i++)
					{
						change = changes[i];
						_data[change] = src[change];
					}
					src.clearChanges();
				}
			}

			void SDistributor::distributeTo(uint_fast8_t sysId)
			{
				if (_containers.count(sysId) > 0)
				{
					auto& dest = _containers.at(sysId)->getData();
					std::copy(_data.begin(), _data.end(), dest.begin());
				}
			}
		}
	}
}