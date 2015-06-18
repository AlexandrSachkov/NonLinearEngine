#ifdef NL_MS_DISTRIBUTOR_H_

#include <cassert>

namespace NLE
{
	namespace Core
	{
		namespace Data
		{
			template<typename T>
			MSDistributor<T>::MSDistributor(uint_fast32_t initialSize) :
				_masterHash(INT_FAST8_MAX, new MasterContainer<T>(initialSize, this)),
				_requestQueue(_requestPool)
			{
				_data.reserve(initialSize);
			}

			template<typename T>
			MSDistributor<T>::~MSDistributor()
			{
				delete _masterHash.second;
				for (auto& i : _slaves)
				{
					delete i.second;
				}
			}

			template<typename T>
			MasterContainer<T>& MSDistributor<T>::buildMasterEndpoint(uint_fast8_t sysId)
			{
				assert(_masterHash.first == INT_FAST8_MAX);
				_masterHash.first = sysId;
				_endpoints.push_back(sysId);
				return *_masterHash.second;
			}

			template<typename T>
			SlaveContainer<T>& MSDistributor<T>::buildSlaveEndpoint(uint_fast8_t sysId)
			{
				assert(_slaves.count(sysId) == 0);
				_slaves.emplace(sysId, new SlaveContainer<T>(_data.size()));
				_endpoints.push_back(sysId);
				return *_slaves.at(sysId);
			}

			template<typename T>
			void MSDistributor<T>::distributeFrom(uint_fast8_t sysId)
			{
				if (_slaves.count(sysId) > 0)
				{
					auto& src = *_slaves.at(sysId);
					src.processRequests();

					auto& changes = src.getChanges();
					for (uint_fast32_t i = 0; i < changes.size(); ++i)
					{
						if (changes[i] == 1)
						{
							_data[i] = src[i];
							changes[i] = 0;
						}					
					}
				}
				else if (_masterHash.first == sysId)
				{
					auto& src = *_masterHash.second;
					auto& changes = src.getChanges();
					for (uint_fast32_t i = 0; i < changes.size(); ++i)
					{
						if (changes[i] == 1)
						{
							_data[i] = src[i];
							changes[i] = 0;
						}
					}
				}
			}

			template<typename T>
			void MSDistributor<T>::distributeTo(uint_fast8_t sysId)
			{
				if (_slaves.count(sysId) > 0)
				{
					auto& dest = *_slaves.at(sysId);
					dest.processRequests();

					auto& destData = dest.getData();
					assert(destData.size() == _data.size());
					std::copy(_data.begin(), _data.end(), destData.begin());
				}
				else if (_masterHash.first == sysId)
				{
					auto& destData = _masterHash.second->getData();
					assert(destData.size() == _data.size());
					std::copy(_data.begin(), _data.end(), destData.begin());
				}
			}

			template<typename T>
			void MSDistributor<T>::queueRequest(MasterRequest<T> request)
			{
				_requestQueue.push(request);
			}

			template<typename T>
			void MSDistributor<T>::processRequests()
			{
				if (_requestQueue.empty())
					return;

				MasterRequest<T> mRequest;
				DistributorRequest dRequest;
				while (_requestQueue.try_pop(mRequest));
				{
					if (mRequest.type == RequestType::ADD)
					{
						_data.push_back(mRequest.payload.data);
					}
					else
					{
						localRemove(mRequest.payload.index);
					}
					dRequest.type = mRequest.type;
					dRequest.index = mRequest.payload.index;

					for (auto& i : _slaves)
					{
						i.second->queueRequest(dRequest);
					}
				}
			}

			template<typename T>
			void MSDistributor<T>::localRemove(uint_fast32_t index)
			{
				size_t size = _data.size();
				assert(index < size);

				size_t lastOccupied = size - 1;
				if (index != lastOccupied)
				{
					_data[index] = _data[lastOccupied];
				}
				_data.pop_back();
			}

			template<typename T>
			std::vector<uint_fast8_t>& MSDistributor<T>::getEndpoints()
			{
				return _endpoints;
			}
		}
	}
}

#endif