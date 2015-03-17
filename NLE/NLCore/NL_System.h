#ifndef NL_SYSTEM_H_
#define NL_SYSTEM_H_

#include "tbb/task.h"

namespace NLE 
{
	namespace Core 
	{

		class System : public tbb::task
		{
		public:
			virtual ~System(){}

			virtual int getID() = 0;
			virtual tbb::task* execute() = 0;
		};
	}
}


#endif