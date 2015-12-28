#ifdef NL_S_CONTAINER_H_


namespace NLE
{
	namespace Core
	{
		namespace Data
		{
			template<typename T>
			SContainer<T>::SContainer(size_t dataSize, size_t queueSize) :
				updateCycle(0)
			{
				_data.resize(dataSize);
				_changes.reserve(queueSize);
			}

			template<typename T>
			SContainer<T>::~SContainer()
			{
			}

			template<typename T>
			size_t SContainer<T>::size()
			{
				return _data.size();
			}		

			template<typename T>
			T const& SContainer<T>::operator[](uint_fast32_t index)
			{
				return _data[index];
			}

			template<typename T>
			void SContainer<T>::modify(uint_fast32_t index, T data)
			{
				_data[index] = data;
				_changes.push_back(index);
			}
			
			template<typename T>
			std::vector<T, tbb::scalable_allocator<T>>& SContainer<T>::getData()
			{
				return _data;
			}

			template<typename T>
			std::vector<uint_fast32_t, tbb::scalable_allocator<uint_fast32_t>> const& SContainer<T>::getChanges()
			{
				return _changes;
			}

			template<typename T>
			void SContainer<T>::clearChanges()
			{
				_changes.clear();
			}
		}
	}
}

#endif