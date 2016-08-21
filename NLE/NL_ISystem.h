#ifndef NL_I_SYSTEM_H_
#define NL_I_SYSTEM_H_

namespace NLE
{
	class SystemServices;
	class DataManager;
	class ISystem
	{
	public:
		virtual void update(SystemServices* sServices, double deltaT) = 0;
	};
}


#endif