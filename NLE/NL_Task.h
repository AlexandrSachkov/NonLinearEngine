#ifndef NL_TASK_H_
#define NL_TASK_H_

#include "tbb\task.h"
#include <functional>

namespace NLE
{
	namespace Core
	{
		class Task : public tbb::task
		{
		public:
			Task(std::function<void()> const& operation) :
				_operation(operation)
			{
			}

			~Task()
			{
			}

			tbb::task* execute()
			{
				_operation();
				return nullptr;
			}

		private:
			std::function<void()> _operation;
		};
	}
}


#endif