#ifndef NL_I_APPLICATION_H_
#define NL_I_APPLICATION_H_

#include "NLCore\NL_ISystem.h"

namespace NLE
{
	class Application;

	class IApplication : public Core::ISystem
	{
	public:
		IApplication(Application& system);
		~IApplication();

		bool initialized();

	private:
		Application* _system;
	};
}

#endif