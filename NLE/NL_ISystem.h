#ifndef NL_I_SYSTEM_H_
#define NL_I_SYSTEM_H_

#include <memory>

namespace NLE
{
	class SystemServices;
	class DataManager;
	class ISystem
	{
	public:
		virtual void update(SystemServices& sServices, double deltaT) = 0;
	};

	typedef std::shared_ptr<ISystem> ISystemSP;
}


#endif