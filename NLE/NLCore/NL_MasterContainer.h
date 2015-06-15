#ifndef NL_MASTER_CONTAINER_H_
#define NL_MASTER_CONTAINER_H_

#include <cstdint>
#include <algorithm>
#include <vector>

#include "NL_DataRequest.h"
#include "tbb\scalable_allocator.h"

namespace NLE
{
	namespace Core
	{
		namespace Data
		{
			template<typename T>
			class MSDistributor;

			template<typename T>
			class MasterContainer
			{
				template<typename T>
				friend class MSDistributor;
			public:
				MasterContainer(size_t initialSize, MSDistributor<T>* distributor);
				~MasterContainer();

				size_t size();
				double const& operator[](uint_fast32_t index);
				void modify(uint_fast32_t index, T data);
				void add(T data);
				void remove(uint_fast32_t index);

				/*
				Convenience removal method which should be used while iterating over the container.

				Since the removal of element at 'index' will cause the container to overwrite it
				with the contents of the last element and remove the last element,
				using a for loop to iterate the container will cause an element to be skipped
				after every removal operation.

				for(int i = 0; i < container.size(); ++i)
				{
				container.remove(i); <-- SKIPPING element at size() - 1 on the next iteration
				}

				This method decrements the index so that the next iteration will occur over the moved element
				*/
				void itRemove(uint_fast32_t& index);

			private:
				MSDistributor<T>* _distributor;
				std::vector<T, tbb::scalable_allocator<T>>& getData();
				std::vector<char, tbb::scalable_allocator<char>>& getChanges();

				std::vector<T, tbb::scalable_allocator<T>> _data;
				std::vector<char, tbb::scalable_allocator<char>> _changes;
			};
		}
	}
}

#include "NL_MasterContainer.inl"

#endif