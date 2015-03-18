#ifndef NL_SYSTEM_H_
#define NL_SYSTEM_H_

namespace NLE 
{
	namespace Core 
	{
		class SysTask;
		class System
		{
		public:
			virtual ~System(){}

			virtual int getID() = 0;
			virtual SysTask* getTask() = 0;
		};
	}
}


#endif