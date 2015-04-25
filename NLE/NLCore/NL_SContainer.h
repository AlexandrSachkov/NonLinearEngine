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
			class SContainer
			{
				friend class SDistributor;
			public:
				SContainer(uint_fast32_t dataSize, uint_fast32_t queueSize);
				~SContainer();

				uint_fast32_t size();			
				double const& operator[](uint_fast32_t index);
				void modify(uint_fast32_t index, double data);

			private:
				std::vector<double, tbb::scalable_allocator<double>>& getData();
				std::vector<uint_fast32_t, tbb::scalable_allocator<uint_fast32_t>> const& getChanges();
				void clearChanges();

				std::vector<double, tbb::scalable_allocator<double>> _data;
				std::vector<uint_fast32_t, tbb::scalable_allocator<uint_fast32_t>> _changes;
			};
		}
	}
}

#endif