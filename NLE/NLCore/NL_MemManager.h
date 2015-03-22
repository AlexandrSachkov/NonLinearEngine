#ifndef NL_MEM_MANAGER_H_
#define NL_MEM_MANAGER_H_

namespace NLE 
{
	namespace Core 
	{
		class MemManager 
		{
		public:
			MemManager();
			~MemManager();

			bool initialize();
			void release();
		};
	}
}

#endif