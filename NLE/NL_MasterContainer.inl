#ifdef NL_MASTER_CONTAINER_H_

#include "NL_MSDistributor.h"
#include <cassert>

namespace NLE
{
	namespace Core
	{
		namespace Data
		{
			template<typename T>
			MasterContainer<T>::MasterContainer(size_t initialSize, MSDistributor<T>* distributor) :
				_distributor(distributor),
				updateCycle(0)
			{
				_data.reserve(initialSize);
				_changes.reserve(initialSize);
			}

			template<typename T>
			MasterContainer<T>::~MasterContainer()
			{
			}

			template<typename T>
			size_t MasterContainer<T>::size()
			{
				return _data.size();
			}

			template<typename T>
			double const& MasterContainer<T>::operator[](uint_fast32_t index)
			{
				return _data[index];
			}

			template<typename T>
			void MasterContainer<T>::modify(uint_fast32_t index, T data)
			{
				_data[index] = data;
				_changes[index] = 1;
			}

			template<typename T>
			void MasterContainer<T>::add(T data)
			{
				_data.push_back(data);
				_changes.push_back(0);
				_distributor->queueRequest({ RequestType::ADD, { data } });
			}

			template<typename T>
			void MasterContainer<T>::remove(uint_fast32_t index)
			{
				size_t size = _data.size();
				assert(index < size);

				size_t lastOccupied = size - 1;
				if (index != lastOccupied)
				{
					_data[index] = _data[lastOccupied];
					_changes[index] = _changes[lastOccupied];
				}
				_data.pop_back();
				_changes.pop_back();

				_distributor->queueRequest({ RequestType::REMOVE, { index } });
			}

			template<typename T>
			void MasterContainer<T>::itRemove(uint_fast32_t& index)
			{
				remove(index);
				--index;
			}

			template<typename T>
			std::vector<T, tbb::scalable_allocator<T>>& MasterContainer<T>::getData()
			{
				return _data;
			}

			template<typename T>
			std::vector<char, tbb::scalable_allocator<char>>& MasterContainer<T>::getChanges()
			{
				return _changes;
			}
		}
	}
}

#endif