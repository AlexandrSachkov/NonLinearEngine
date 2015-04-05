#ifdef NL_DATA_DISTRIBUTOR_H_

#include "NL_DataContainer.h"

namespace NLE
{
	namespace Core
	{
		template<typename T>
		DataDistributor<T>::DataDistributor() :
			_packets(),
			_listeners()
		{
		}

		template<typename T>
		DataDistributor<T>::~DataDistributor()
		{
		}

		template<typename T>
		inline void DataDistributor<T>::bindContainer(DataContainer<T>* dataContainer)
		{
			dataContainer->bindDistributor(this);
			_listeners.push_back(dataContainer);
		}

		template<typename T>
		inline void DataDistributor<T>::queue(DataPacket<T> packet)
		{
			_packets.push(packet);
		}

		template<typename T>
		void DataDistributor<T>::distribute()
		{
			DataPacket<T> packet;
			while (_packets.try_pop(packet))
			{
				for (uint_fast8_t i = 0; i < _listeners.size(); ++i)
				{
					if (i != packet.getSysId())
					{
						_listeners[i]->queuePacket(packet);
					}
				}
			}
		}
	}
}

#endif