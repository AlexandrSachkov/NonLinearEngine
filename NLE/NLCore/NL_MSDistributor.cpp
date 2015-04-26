#include "NL_MSDistributor.h"
#include <cassert>

namespace NLE
{
	namespace Core
	{
		namespace Data
		{
			MSDistributor::MSDistributor(uint_fast32_t initialSize) :
				_masterHash(INT_FAST8_MAX, new MasterContainer(initialSize, this)),
				_requestQueue(_requestPool)
			{
				_data.reserve(initialSize);
			}

			MSDistributor::~MSDistributor()
			{
				delete _masterHash.second;
				for (auto& i : _slaves)
				{
					delete i.second;
				}
			}

			MasterContainer& MSDistributor::buildMasterEndpoint(uint_fast8_t sysId)
			{
				assert(_masterHash.first == INT_FAST8_MAX);
				_masterHash.first = sysId;
				return *_masterHash.second;
			}

			SlaveContainer& MSDistributor::buildSlaveEndpoint(uint_fast8_t sysId)
			{
				assert(_slaves.count(sysId) == 0);
				_slaves.emplace(sysId, new SlaveContainer(_data.size()));
				return *_slaves.at(sysId);
			}

			void MSDistributor::distributeFrom(uint_fast8_t sysId)
			{
				if (_slaves.count(sysId) > 0)
				{
					auto& src = *_slaves.at(sysId);
					auto& changes = src.getChanges();
					for (uint_fast32_t i = 0; i < changes.size(); i++)
					{
						if (changes[i] == 1)
						{
							_data[i] = src[i];
							changes[i] = 0;
						}					
					}
				}
				if (_masterHash.first == sysId)
				{
					auto& src = *_masterHash.second;
					auto& changes = src.getChanges();
					for (uint_fast32_t i = 0; i < changes.size(); i++)
					{
						if (changes[i] == 1)
						{
							_data[i] = src[i];
							changes[i] = 0;
						}
					}
				}
			}

			void MSDistributor::distributeTo(uint_fast8_t sysId)
			{
				if (_slaves.count(sysId) > 0)
				{
					auto& dest = _slaves.at(sysId)->getData();
					assert(dest.size() == _data.size());
					std::copy(_data.begin(), _data.end(), dest.begin());
				}
				if (_masterHash.first == sysId)
				{
					auto& dest = _masterHash.second->getData();
					assert(dest.size() == _data.size());
					std::copy(_data.begin(), _data.end(), dest.begin());
				}
			}

			void MSDistributor::queueRequest(MasterRequest request)
			{
				_requestQueue.push(request);
			}

			void MSDistributor::processRequests()
			{
				MasterRequest mRequest;
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

					_masterHash.second->queueRequest(dRequest);
					for (auto& i : _slaves)
					{
						i.second->queueRequest(dRequest);
					}
				}
			}

			void MSDistributor::localRemove(uint_fast32_t index)
			{
				uint_fast32_t size = _data.size();
				assert(index < size);

				uint_fast32_t lastOccupied = size - 1;
				if (index != lastOccupied)
				{
					_data[index] = _data[lastOccupied];
				}
				_data.pop_back();
			}
		}
	}
}