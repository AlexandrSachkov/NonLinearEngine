#ifndef NL_STATE_MANAGER_H_
#define NL_STATE_MANAGER_H_

#include "NL_MSDistributor.h"
#include "NL_SDistributor.h"
#include "tbb\tbb.h"
#include "tbb\scalable_allocator.h"
#include "tbb\concurrent_unordered_map.h"

#include <cstdint>
#include <vector>
#include <assert.h>

namespace NLE
{
	namespace Core
	{
		class StateManager
		{
		public:
			StateManager() :
				_initialized(false)
			{

			}

			~StateManager()
			{
				release();
			}

			bool initialize()
			{
				assert(!_initialized);

				for (auto distributor : _sDistributors)
				{
					mapDistributor(distributor);
				}
				for (auto distributor : _msDistributors)
				{
					mapDistributor(distributor);
				}
				return true;
			}

			void release()
			{
				for (auto& i : _sDistributors)
				{
					delete i;
				}
				for (auto& i : _msDistributors)
				{
					delete i;
				}
				_sDistributorIndex.clear();
				_msDistributorIndex.clear();

				for (auto it = _sdMap.begin(); it != _sdMap.end(); ++it)
				{
					delete it->second;
				}
				_sdMap.clear();
				_initialized = true;
			}

			void processRequests()
			{
				tbb::parallel_for(
					tbb::blocked_range<size_t>(0, _msDistributors.size()),
					[&](const tbb::blocked_range<size_t>& r)
				{
					for (size_t i = r.begin(); i < r.end(); ++i)
					{
						_msDistributors[i]->processRequests();
					}
				});
			}

			void distributeFrom(uint_fast32_t sysId)
			{
				if (_sdMap.count(sysId) > 0)
				{
					auto distributors = _sdMap.at(sysId);
					tbb::parallel_for(
						tbb::blocked_range<size_t>(0, distributors->size()),
						[&](const tbb::blocked_range<size_t>& r)
					{
						for (size_t i = r.begin(); i < r.end(); ++i)
						{
							distributors->at(i)->distributeFrom(sysId);
						}
					});
				}
			}

			void distributeTo(uint_fast32_t sysId)
			{
				if (_sdMap.count(sysId) > 0)
				{
					auto distributors = _sdMap.at(sysId);
					tbb::parallel_for(
						tbb::blocked_range<size_t>(0, distributors->size()),
						[&](const tbb::blocked_range<size_t>& r)
					{
						for (size_t i = r.begin(); i < r.end(); ++i)
						{
							distributors->at(i)->distributeTo(sysId);
						}
					});
				}
			}

			template <typename T>
			void installMSContainer(uint_fast32_t id, uint_fast32_t initialSize, uint_fast32_t grainSize)
			{
				assert(!_initialized);

				Data::Distributor* distributor = new Data::MSDistributor<T>(initialSize, grainSize);
				_msDistributors.push_back(distributor);
				_msDistributorIndex.insert(std::make_pair<>(id, distributor));
			}

			template <typename T>
			void installSContainer(uint_fast32_t id, uint_fast32_t size, uint_fast32_t grainSize)
			{
				assert(!_initialized);

				Data::Distributor* distributor = new Data::SDistributor<T>(size, size / 4, grainSize);
				_sDistributors.push_back(distributor);
				_sDistributorIndex.insert(std::make_pair<>(id, distributor));
			}

			Data::Distributor& getSDistributor(uint_fast32_t id)
			{
				return *_sDistributorIndex.at(id);
			}

			Data::Distributor& getMSDistributor(uint_fast32_t id)
			{
				return *_msDistributorIndex.at(id);
			}
			

		private:
			void mapDistributor(Data::Distributor* distributor)
			{
				auto& endpoints = distributor->getEndpoints();
				for (auto& sysId : endpoints)
				{
					if (_sdMap.count(sysId) > 0)
					{
						_sdMap.at(sysId)->push_back(distributor);
					}
					else
					{
						_sdMap.insert(std::make_pair<>(
							sysId,
							new std::vector<Data::Distributor*, tbb::scalable_allocator<Data::Distributor*>>()
							));
						_sdMap.at(sysId)->push_back(distributor);
					}
				}
			}

			std::vector<Data::Distributor*, tbb::scalable_allocator<Data::Distributor*>> _sDistributors;
			std::vector<Data::Distributor*, tbb::scalable_allocator<Data::Distributor*>> _msDistributors;

			tbb::concurrent_unordered_map<uint_fast32_t, Data::Distributor*> _sDistributorIndex;
			tbb::concurrent_unordered_map<uint_fast32_t, Data::Distributor*> _msDistributorIndex;
			
			std::unordered_map<uint_fast32_t, std::vector<Data::Distributor*, tbb::scalable_allocator<Data::Distributor*>>*> _sdMap;

			bool _initialized;
		};
	}
}

#endif