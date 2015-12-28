#ifdef NL_DEVICE_CORE_H_

#include "NL_StateManager.h"

namespace NLE
{
	namespace Core
	{
		template <typename T>
		void DeviceCore::installMSContainer(uint_fast32_t id, uint_fast32_t initialSize, uint_fast32_t grainSize)
		{
			_stateManager->installMSContainer<T>(id, initialSize, grainSize);
		}

		template <typename T>
		void DeviceCore::installSContainer(uint_fast32_t id, uint_fast32_t size, uint_fast32_t grainSize)
		{
			_stateManager->installSContainer<T>(id, size, grainSize);
		}
	}
}

#endif