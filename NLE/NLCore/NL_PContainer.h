#ifndef NL_P_CONTAINER_H_
#define NL_P_CONTAINER_H_

#include <algorithm>
#include <vector>

#include "tbb\scalable_allocator.h"

namespace NLE
{
	namespace Core
	{
		namespace Data
		{
			class PContainer
			{
			public:
				PContainer(uint_fast32_t size);
				~PContainer();

				void add(double data);
				void remove(uint_fast32_t index);
				void modify(uint_fast32_t index, double data);
				void clear();

				uint_fast32_t size();
				double& get(uint_fast32_t index);

			private:
				std::vector<double, tbb::scalable_allocator<double>> _data;
			};
		}

	}
}

//#include "NL_DataContainer.inl"

#endif