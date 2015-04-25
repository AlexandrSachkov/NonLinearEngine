#ifndef NL_P_CONTAINER_H_
#define NL_P_CONTAINER_H_

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
			class PContainer
			{
			public:
				PContainer(uint_fast32_t size);
				~PContainer();

				void add(T data);
				void remove(uint_fast32_t index);
				void clear();

				uint_fast32_t size();
				T& operator[](uint_fast32_t index);

			private:
				std::vector<T, tbb::scalable_allocator<T>> _data;
			};
		}

	}
}

#include "NL_PContainer.inl"

#endif