#ifndef NL_APPLICATION_H_
#define NL_APPLICATION_H_

#include "NLCore\NL_System.h"
#include <functional>

namespace NLE
{
	class Core::IEngine;
	class Core::ISystem;
	class IApplication;
	class Window;
	
	class Application : public Core::System
	{
	public:
		Application();
		~Application();

		bool initialize(Core::IEngine& engine);
		void release();
		bool initialized();

		std::function<void()> getExecutionProcedure();
		Core::ISystem& getInterface();

	private:
		bool _initialized;
		std::function<void()> _procedure;
		IApplication* _interface;
	};
}

#endif