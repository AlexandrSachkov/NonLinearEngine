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
			class MSDistributor;

			class MasterContainer
			{
				friend class MSDistributor;
			public:
				MasterContainer(uint_fast32_t initialSize, MSDistributor* distributor);
				~MasterContainer();

				uint_fast32_t size();
				double const& operator[](uint_fast32_t index);
				void modify(uint_fast32_t index, double data);
				void add(double data);
				void remove(uint_fast32_t index);

			private:
				MSDistributor* _distributor;
				std::vector<double, tbb::scalable_allocator<double>>& getData();
				std::vector<char, tbb::scalable_allocator<char>>& getChanges();

				std::vector<double, tbb::scalable_allocator<double>> _data;
				std::vector<char, tbb::scalable_allocator<char>> _changes;
			};
		}
	}
}


#endif