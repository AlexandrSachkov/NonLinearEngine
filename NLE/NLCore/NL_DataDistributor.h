#ifndef NL_DATA_DISTRIBUTOR_H_
#define NL_DATA_DISTRIBUTOR_H_

#include <vector>
#include "tbb\concurrent_queue.h"

#include "NL_DataPacket.h"

namespace NLE
{
	namespace Core
	{
		template<typename T>
		class DataContainer;

		template<typename T>
		class DataDistributor
		{
		public:
			DataDistributor();
			~DataDistributor();

			void bindContainer(DataContainer<T>* dataContainer);
			void queue(DataPacket<T> packet);
			void distribute();

		private:
			tbb::concurrent_queue<DataPacket<T>> _packets;
			std::vector<DataContainer<T>*> _listeners;
		};
	}
}

#include "NL_DataDistributor.inl"

#endif