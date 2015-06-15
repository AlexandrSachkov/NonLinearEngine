#ifndef NL_S_CONTAINER_H_
#define NL_S_CONTAINER_H_

#include <cstdint>
#include <algorithm>
#include <vector>

#include "tbb\scalable_allocator.h"

namespace NLE
{
	namespace Core
	{
		namespace Data
		{
			template<typename T>
			class SContainer
			{
				template<typename T>
				friend class SDistributor;
			public:
				SContainer(size_t dataSize, size_t queueSize);
				~SContainer();

				size_t size();			
				T const& operator[](uint_fast32_t index);
				void modify(uint_fast32_t index, T data);

			private:
				std::vector<T, tbb::scalable_allocator<T>>& getData();
				std::vector<uint_fast32_t, tbb::scalable_allocator<uint_fast32_t>> const& getChanges();
				void clearChanges();

				std::vector<T, tbb::scalable_allocator<T>> _data;
				std::vector<uint_fast32_t, tbb::scalable_allocator<uint_fast32_t>> _changes;
			};
		}
	}
}

#include "NL_SContainer.inl"

#endif