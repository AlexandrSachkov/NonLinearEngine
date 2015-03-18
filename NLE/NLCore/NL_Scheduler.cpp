#include "NL_Scheduler.h"
#include "tbb/tbb.h"

namespace NLE
{
	namespace Core
	{
		Scheduler::Scheduler()
		{

		}

		Scheduler::~Scheduler()
		{

		}

		bool Scheduler::initialize()
		{
			tbb::task_scheduler_init init(tbb::task_scheduler_init::automatic);
			return true;
		}

		void Scheduler::release()
		{

		}
	}
}