#ifndef NL_SYSTEM_H_
#define NL_SYSTEM_H_

#include <cstdint>
#include <memory>
#include <functional>

#include "NL_StateManager.h"
#include "NL_IEngine.h"

namespace NLE 
{
	namespace Core 
	{
		class System
		{
		public:
			virtual ~System(){}

			virtual bool initialize(
				uint_fast32_t id,
				IEngine& iEngine) = 0;
			virtual void release() = 0;
			virtual std::function<void()> getExecutionProcedure() = 0;	
		};		
	}
}

#endif