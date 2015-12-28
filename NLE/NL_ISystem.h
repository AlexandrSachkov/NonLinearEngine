#ifndef NL_I_SYSTEM_H_
#define NL_I_SYSTEM_H_

namespace NLE
{
	namespace Core
	{
		class ISystem
		{
		public:
			virtual bool initialized() = 0;
		};
	}
}

#endif