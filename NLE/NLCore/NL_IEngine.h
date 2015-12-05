#ifndef NL_I_ENGINE_H_
#define NL_I_ENGINE_H_

#include <memory>

namespace NLE
{
	namespace Core
	{
		namespace Data
		{
			class Distributor;
		}

		class ISystem;
		class IEngine
		{
		public:
			virtual void startSystem(uint_fast32_t sysId) = 0;
			virtual void stopSystem(uint_fast32_t sysId) = 0;
			virtual uint_fast32_t getNumThreads() = 0;
			virtual uint_fast32_t getNumSystems() = 0;
			virtual ISystem& getSystemInterface(uint_fast32_t sysId) = 0;
			virtual Data::Distributor& getSDistributor(uint_fast32_t id) = 0;
			virtual Data::Distributor& getMSDistributor(uint_fast32_t id) = 0;

		};
	}
}

#endif