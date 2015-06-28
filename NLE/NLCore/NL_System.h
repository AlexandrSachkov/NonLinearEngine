#ifndef NL_SYSTEM_H_
#define NL_SYSTEM_H_

#include <cstdint>
#include <memory>
#include <functional>

namespace NLE 
{
	namespace Core 
	{
		class IEngine;
		class ISystem;
		class System
		{
		public:
			virtual ~System(){}

			virtual bool initialize(IEngine& engine) = 0;
			virtual void release() = 0;
			virtual std::function<void()> const& getExecutionProcedure() = 0;	
			virtual ISystem& getInterface() = 0;
		};		
	}
}

#endif