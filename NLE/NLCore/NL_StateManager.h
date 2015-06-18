#ifndef NL_STATE_MANAGER_H_
#define NL_STATE_MANAGER_H_

#include "NL_MSDistributor.h"
#include "NL_SDistributor.h"
#include "tbb\scalable_allocator.h"
#include "tbb\concurrent_unordered_map.h"

#include <cstdint>
#include <vector>

namespace NLE
{
	namespace Core
	{
		class StateManager
		{
		public:
			StateManager()
			{

			}

			~StateManager()
			{

			}

			bool initialize()
			{
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
				_sdMap.clear();
			}

			void processRequests()
			{
				for (auto& msDist : _msDistributors)
				{
					msDist->processRequests();
				}
			}

			void distributeFrom(uint_fast8_t sysId)
			{
				if (_sdMap.count(sysId) > 0)
				{
					auto distributors = _sdMap.at(sysId);
					for (uint_fast32_t i = 0; i < distributors->size(); ++i)
					{
						distributors->at(i)->distributeFrom(sysId);
					}
				}
			}

			void distributeTo(uint_fast8_t sysId)
			{
				if (_sdMap.count(sysId) > 0)
				{
					auto distributors = _sdMap.at(sysId);
					for (uint_fast32_t i = 0; i < distributors->size(); ++i)
					{
						distributors->at(i)->distributeTo(sysId);
					}
				}
			}

			template <typename T>
			void installMSContainer(unsigned int id, uint_fast32_t initialSize)
			{
				Data::Distributor* distributor = new Data::MSDistributor<T>(initialSize);
				_msDistributors.push_back(distributor);
				_msDistributorIndex.insert(std::make_pair<>(id, distributor));
			}

			template <typename T>
			void installSContainer(unsigned int id, uint_fast32_t size)
			{
				Data::Distributor* distributor = new Data::SDistributor<T>(size, size / 4);
				_sDistributors.push_back(distributor);
				_sDistributorIndex.insert(std::make_pair<>(id, distributor));
			}

			template <typename T>
			Data::SDistributor<T>& getSDistributor(unsigned int id)
			{
				return *static_cast<Data::SDistributor<T>*>(_sDistributorIndex.at(id));
			}

			template <typename T>
			Data::MSDistributor<T>& getMSDistributor(unsigned int id)
			{
				return *static_cast<Data::MSDistributor<T>*>(_msDistributorIndex.at(id));
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

			tbb::concurrent_unordered_map<unsigned int, Data::Distributor*> _sDistributorIndex;
			tbb::concurrent_unordered_map<unsigned int, Data::Distributor*> _msDistributorIndex;
			
			std::unordered_map<unsigned int, std::vector<Data::Distributor*, tbb::scalable_allocator<Data::Distributor*>>*> _sdMap;
		};
	}
}

#endif