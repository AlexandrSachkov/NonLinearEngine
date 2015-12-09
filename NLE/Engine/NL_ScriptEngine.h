#ifndef NL_SCRIPT_ENGINE_H_
#define NL_SCRIPT_ENGINE_H_

#include "NL_IScriptEngine.h"
#include "NLCore\NL_System.h"
#include "NLCore\NL_SContainer.h"

#include "tbb\atomic.h"
#include "tbb\concurrent_queue.h"

#include <string>

namespace NLE
{
	namespace SCRIPT
	{
		class ScriptEngine : public Core::System, public IScriptEngine
		{
		public:
			ScriptEngine();
			~ScriptEngine();

			bool initialize(Core::IEngine& engine);
			void release();

			bool initialized();

			std::function<void()> const& getExecutionProcedure();
			Core::ISystem& getInterface();

			void executeScript(const char* script);

		private:
			bool _initialized;
			tbb::atomic<bool> _running;
			std::function<void()> _procedure;

			tbb::concurrent_queue<std::string> _scripts;
		};
	}
}

#endif
