#ifdef NL_S_DISTRIBUTOR_H_

#include <cassert>

namespace NLE
{
	namespace Core
	{
		namespace Data
		{
			template<typename T>
			SDistributor<T>::SDistributor(uint_fast32_t dataSize, uint_fast32_t queueSize) :
				_queueSize(queueSize)
			{
				_data.resize(dataSize);
			}

			template<typename T>
			SDistributor<T>::~SDistributor()
			{
				for (auto& i : _containers)
				{
					delete i.second;
				}
			}

			template<typename T>
			SContainer<T>& SDistributor<T>::buildEndpoint(uint_fast8_t sysId)
			{
				assert(_containers.count(sysId) == 0);
				_containers.emplace(sysId, new SContainer<T>(_data.size(), _queueSize));
				return *_containers.at(sysId);
			}

			template<typename T>
			void SDistributor<T>::distributeFrom(uint_fast8_t sysId)
			{
				if (_containers.count(sysId) > 0)
				{
					auto& src = *_containers.at(sysId);
					auto const& changes = src.getChanges();
					uint_fast32_t change;
					for (uint_fast32_t i = 0; i < changes.size(); ++i)
					{
						change = changes[i];
						_data[change] = src[change];
					}
					src.clearChanges();
				}
			}

			template<typename T>
			void SDistributor<T>::distributeTo(uint_fast8_t sysId)
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


#endif