#ifdef NL_SLAVE_CONTAINER_H_

#include <cassert>

namespace NLE
{
	namespace Core
	{
		namespace Data
		{
			template<typename T>
			SlaveContainer<T>::SlaveContainer(size_t initialSize) :
				_requestQueue(_requestPool)
			{
				_data.reserve(initialSize);
				_changes.reserve(initialSize);
			}

			template<typename T>
			SlaveContainer<T>::~SlaveContainer()
			{
			}

			template<typename T>
			size_t SlaveContainer<T>::size()
			{
				return _data.size();
			}

			template<typename T>
			double const& SlaveContainer<T>::operator[](uint_fast32_t index)
			{
				return _data[index];
			}

			template<typename T>
			void SlaveContainer<T>::modify(uint_fast32_t index, T data)
			{
				_data[index] = data;
				_changes[index] = 1;
			}

			template<typename T>
			void SlaveContainer<T>::queueRequest(DistributorRequest request)
			{
				_requestQueue.push(request);
			}

			template<typename T>
			void SlaveContainer<T>::processRequests()
			{
				if (_requestQueue.empty())
					return;

				DistributorRequest request;
				while (_requestQueue.try_pop(request))
				{
					if (request.type == RequestType::ADD)
					{
						growByOne();
					}
					else
					{
						localRemove(request.index);
					}
				}
			}

			template<typename T>
			void SlaveContainer<T>::growByOne()
			{
				_data.resize(_data.size() + 1);
				_changes.push_back(0);
			}

			template<typename T>
			void SlaveContainer<T>::localRemove(uint_fast32_t index)
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
			}

			template<typename T>
			std::vector<T, tbb::scalable_allocator<T>>& SlaveContainer<T>::getData()
			{
				return _data;
			}

			template<typename T>
			std::vector<char, tbb::scalable_allocator<char>>& SlaveContainer<T>::getChanges()
			{
				return _changes;
			}
		}
	}
}

#endif