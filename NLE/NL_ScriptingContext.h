#ifndef NL_SCRIPTING_CONTEXT_H_
#define NL_SCRIPTING_CONTEXT_H_

#include "NL_Map.h"

namespace NLE
{
	namespace SCRIPT
	{
		static const std::wstring ON_INIT = L"onInit";
		static const std::wstring ON_UPDATE = L"onUpdate";
		static const std::wstring ON_EXIT = L"onExit";

		class ScriptingContext
		{
		public:
			ScriptingContext();
			~ScriptingContext();

			void addScript(std::wstring name, std::wstring script);
			std::wstring getScript(std::wstring name);
			void removeScript(std::wstring name);
			void addData(std::wstring name, std::wstring data);
			std::wstring getData(std::wstring name);
			void removeData(std::wstring name);			

		private:
			Map<std::wstring, std::wstring, REPLACE> _scripts;
			Map<std::wstring, std::wstring, REPLACE> _data;
		};
	}
}

#endif