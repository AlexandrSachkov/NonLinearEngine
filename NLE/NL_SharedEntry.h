#pragma once

#include "NL_ISharedEntity.h"
#include "NL_IDataManager.h"

#include "tbb/spin_mutex.h"

namespace NLE
{
	namespace DATA
	{
		template<typename T>
		class SharedEntry : public ISharedEntity
		{
		public:
			SharedEntry(IDataManager_Data& dataManager) : 
				_dataManager(dataManager),
				_updated(false)
			{
			}

			SharedEntry(IDataManager_Data& dataManager, T value) : 
				_dataManager(dataManager), 
				_source(value),
				_destination(value),
				_updated(false)
			{
			}

			~SharedEntry()
			{
			}

			T get()
			{
				return _source;
			}

			void set(T value)
			{
				_updateLock.lock();
				_destination = value;
				if (!_updated)
				{
					_updated = true;
					_dataManager.requestSync(this);
				}
				_updateLock.unlock();
			}

			void sync()
			{
				_source = _destination;
				_updated = false;
			}

		private:
			tbb::spin_mutex _updateLock;
			IDataManager_Data& _dataManager;
			T _source;
			T _destination;
			bool _updated;
		};
	}
}