#ifndef NL_DISTRIBUTOR_H_
#define NL_DISTRIBUTOR_H_

#include <cstdint>

namespace NLE
{
	namespace Core
	{
		namespace Data
		{
			class Distributor
			{
			public:
				virtual void distributeFrom(uint_fast8_t sysId) = 0;
				virtual void distributeTo(uint_fast8_t sysId) = 0;
				virtual void processRequests(){}
			};
		}
	}
}


#endif