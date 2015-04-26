#ifndef NL_EXECUTION_DESC_H_
#define NL_EXECUTION_DESC_H_

#include <cstdint>

namespace NLE
{
	namespace Core
	{
		enum Priority { LOW, STANDARD, HIGH };

		class ExecutionDesc
		{
		public:
			//Only used when popping from queue
			ExecutionDesc() :
				_priority(Priority::LOW),
				_sysId(-1)
			{
			}

			ExecutionDesc(Priority priority, uint_fast8_t sysId) :
				_priority(priority),
				_sysId(sysId)
			{
			}

			~ExecutionDesc()
			{
			}

			Priority getPriority() const
			{
				return _priority;
			}

			uint_fast8_t getSysId() const
			{
				return _sysId;
			}

		private:
			Priority _priority;
			uint_fast8_t _sysId;
		};
	}
}

#endif