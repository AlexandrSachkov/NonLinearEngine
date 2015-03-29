#ifndef NL_DATA_MANAGER_H_
#define NL_DATA_MANAGER_H_

#include <cstdint>
#include <memory>
#include <unordered_map>

namespace NLE
{
	namespace Core
	{
		class SysData;
		class DataManager
		{
		public:
			DataManager();
			~DataManager();

			bool initialize(uint_fast8_t numSystems);
			void release();

			std::unique_ptr<SysData> const& getDataHandle(uint_fast8_t sysId);

		private:
			std::unique_ptr<SysData> _sharedData;
			std::unordered_map<uint_fast8_t, std::unique_ptr<SysData>> _sysData;
		};
	}
}

#endif