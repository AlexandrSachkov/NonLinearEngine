#ifndef NL_EXECUTION_DESC_H_
#define NL_EXECUTION_DESC_H_

#include <cstdint>

namespace NLE
{
	namespace Core
	{
		enum ExecutionType { SYNC, ASYNC };
		enum Priority { LOW, STANDARD, HIGH };

		class ExecutionDesc
		{
		public:
			//Only used when popping from queue
			ExecutionDesc() :
				_execType(ExecutionType::SYNC),
				_priority(Priority::LOW),
				_sysId(-1)
			{
			}

			ExecutionDesc(ExecutionType execType, Priority priority, uint_fast8_t sysId) :
				_execType(execType),
				_priority(priority),
				_sysId(sysId)
			{
			}

			~ExecutionDesc()
			{
			}

			ExecutionType getExecutionType() const
			{
				return _execType;
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
			ExecutionType _execType;
			Priority _priority;
			uint_fast8_t _sysId;
		};
	}
}

#endif