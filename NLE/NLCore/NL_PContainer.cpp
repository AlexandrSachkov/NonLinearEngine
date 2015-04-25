//#ifdef NL_DATA_CONTAINER_H_

#include "NL_PContainer.h"

namespace NLE
{
	namespace Core
	{
		namespace Data
		{
			PContainer::PContainer(uint_fast32_t size) :
				_data()
			{
				_data.reserve(size);
			}

			PContainer::~PContainer()
			{
			}

			inline void PContainer::add(double data)
			{
				_data.push_back(data);
			}

			void PContainer::remove(uint_fast32_t index)
			{
				uint_fast32_t size = _data.size();
				if (index < size)
				{
					uint_fast32_t lastOccupied = size - 1;
					if (index != lastOccupied)
					{
						_data[index] = _data[lastOccupied];
					}
					_data.pop_back();
				}
			}

			inline void PContainer::modify(uint_fast32_t index, double data)
			{
				_data[index] = data;
			}

			inline void PContainer::clear()
			{
				_data.clear();
			}

			inline uint_fast32_t PContainer::size()
			{
				return _data.size();
			}

			inline double& PContainer::get(uint_fast32_t index)
			{
				return _data[index];
			}
		}

	}
}

//#endif