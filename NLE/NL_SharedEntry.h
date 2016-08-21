#ifndef NL_SHARED_ENTRY_H_
#define NL_SHARED_ENTRY_H_

#include "NL_ISharedEntity.h"
#include "NL_Atomic.h"
#include "NL_IDataManager.h"

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

			void requestUpdate(T value)
			{
				_destination.set(value);
				bool updated = _updated.acquire();
				if (!updated)
				{
					updated = true;
					_dataManager.requestSync(this);
				}
				_updated.release();
			}

			void sync()
			{
				_source = _destination.get();
				_updated.set(false);
			}

		private:
			IDataManager_Data& _dataManager;
			T _source;
			Atomic<T> _destination;
			Atomic<bool> _updated;
		};
	}
}

#endif