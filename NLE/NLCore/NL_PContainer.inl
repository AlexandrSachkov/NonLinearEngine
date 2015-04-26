#ifdef NL_P_CONTAINER_H_

#include <cassert>

namespace NLE
{
	namespace Core
	{
		namespace Data
		{
			template<typename T>
			PContainer<T>::PContainer(uint_fast32_t size)
			{
				_data.reserve(size);
			}

			template<typename T>
			PContainer<T>::~PContainer()
			{
			}

			template<typename T>
			inline void PContainer<T>::add(T data)
			{
				_data.push_back(data);
			}

			template<typename T>
			void PContainer<T>::remove(uint_fast32_t index)
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

			template<typename T>
			inline void PContainer<T>::clear()
			{
				_data.clear();
			}

			template<typename T>
			inline uint_fast32_t PContainer<T>::size()
			{
				return _data.size();
			}

			template<typename T>
			inline T& PContainer<T>::operator[](uint_fast32_t index)
			{
				return _data[index];
			}
		}
	}
}

#endif