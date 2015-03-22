#ifndef NL_UOBJECT_H_
#define NL_UOBJECT_H_

#include <cstdint>

namespace NLE 
{
	namespace Core 
	{
		class SObject;
		class UObject 
		{
		public:
			virtual ~UObject();
			virtual SObject* getSysObject(uint_fast8_t sysId) = 0;
		};
	}
}

#endif