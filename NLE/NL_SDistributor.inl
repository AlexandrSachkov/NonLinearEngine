#ifdef NL_S_DISTRIBUTOR_H_

#include <cassert>
#include "tbb\tbb.h"

namespace NLE
{
	namespace Core
	{
		namespace Data
		{
			template<typename T>
			SDistributor<T>::SDistributor(uint_fast32_t dataSize, uint_fast32_t queueSize, uint_fast32_t grainSize) :
				_queueSize(queueSize),
				_grainSize(grainSize),
				_updateCycle(0)
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
			SContainer<T>& SDistributor<T>::buildEndpoint(uint_fast32_t sysId)
			{
				assert(_containers.count(sysId) == 0);
				SContainer<T>* container = new SContainer<T>(_data.size(), _queueSize);
				_containers.emplace(sysId, container);
				_endpoints.push_back(sysId);
				return *_containers.at(sysId);
			}

			template<typename T>
			void SDistributor<T>::distributeFrom(uint_fast32_t sysId)
			{
				if (_containers.count(sysId) > 0)
				{
					auto& src = *_containers.at(sysId);
					auto const& changes = src.getChanges();

					if (changes.size() > 0)
					{
						tbb::parallel_for(
							tbb::blocked_range<size_t>(0, changes.size(), _grainSize),
							[&](const tbb::blocked_range<size_t>& r)
						{
							uint_fast32_t change;
							for (size_t i = r.begin(); i < r.end(); ++i)
							{
								change = changes[i];
								_data[change] = src[change];
							}
						});
						src.clearChanges();

						++_updateCycle;
						src.updateCycle = _updateCycle;
					}
				}
			}

			template<typename T>
			void SDistributor<T>::distributeTo(uint_fast32_t sysId)
			{
				if (_containers.count(sysId) > 0)
				{
					auto container = _containers.at(sysId);
					if (container->updateCycle != _updateCycle)
					{
						auto& dest = container->getData();
						tbb::parallel_for(
							tbb::blocked_range<size_t>(0, _data.size(), _grainSize),
							[&](const tbb::blocked_range<size_t>& r)
						{
							std::copy(_data.begin() + r.begin(), _data.begin() + r.end(), dest.begin() + r.begin());
						});
						container->updateCycle = _updateCycle;
					}
				}
			}

			template<typename T>
			std::vector<uint_fast32_t>& SDistributor<T>::getEndpoints()
			{
				return _endpoints;
			}
		}
	}
}


#endif