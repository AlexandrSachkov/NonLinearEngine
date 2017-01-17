#pragma once

#include "NL_ISharedEntity.h"
#include "NL_IDataManager.h"

#include <vector>
#include <algorithm>
#include <assert.h>

#include "tbb/spin_mutex.h"

namespace NLE
{
	namespace DATA
	{
		template<typename T>
		class SharedArray : public ISharedEntity
		{
		public:
			SharedArray(IDataManager_Data& dataManager, size_t size) :
				_dataManager(dataManager),
				_source(size),
				_destination(size),
				_updated(false)

			{
			}

			SharedArray(IDataManager_Data& dataManager, size_t size, T value) :
				_dataManager(dataManager),
				_source(size),
				_destination(size),
				_updated(false)
			{
				std::fill(_source.begin(), _source.end(), value);
				std::fill(_destination.begin(), _destination.end(), value);
			}

			~SharedArray()
			{
			}

			const std::vector<T>& get()
			{
				return _source;
			}

			void fill(T value)
			{
				_updateLock.lock();
				std::fill(_destination.begin(), _destination.end(), value);
				requestSync();
				_updateLock.unlock();
			}

			void set(size_t index, T value)
			{
				_updateLock.lock();
				_destination[index] = value;
				requestSync();
				_updateLock.unlock();
			}

			void set(std::vector<T> values)
			{
				if (values.size() != _destination.size())
					assert(false);

				_updateLock.lock();
				_destination = values;
				requestSync();
				_updateLock.unlock();
			}

			void sync()
			{
				_source = _destination;
				_updated = false;
			}

		private:
			void requestSync()
			{
				if (!_updated)
				{
					_updated = true;
					_dataManager.requestSync(this);
				}
			}

			tbb::spin_mutex _updateLock;
			IDataManager_Data& _dataManager;
			std::vector<T> _source;
			std::vector<T> _destination;
			bool _updated;
		};
	}
}