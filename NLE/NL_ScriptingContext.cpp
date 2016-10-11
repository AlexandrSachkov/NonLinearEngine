#include "NL_ScriptingContext.h"

namespace NLE
{
	namespace SCRIPT
	{
		ScriptingContext::ScriptingContext()
		{
			addScript(ON_INIT, L"");
			addScript(ON_UPDATE, L"");
			addScript(ON_EXIT, L"");
		}

		ScriptingContext::~ScriptingContext()
		{
		}

		void ScriptingContext::addScript(std::wstring name, std::wstring script)
		{
			if (name.compare(L"") == 0) return;
			_scripts.insert(name, script);
			_scriptStatus.insert(name, { true, L""});
		}

		std::wstring ScriptingContext::getScript(std::wstring name)
		{
			if (name.compare(L"") == 0) return L"";

			std::wstring script;
			if (_scripts.get(name, script))
			{
				return script;
			}
			return L"";
		}

		void ScriptingContext::removeScript(std::wstring name)
		{
			if (name.compare(L"") == 0) return;
			else if (name.compare(ON_INIT) == 0) return;
			else if (name.compare(ON_UPDATE) == 0) return;
			else if (name.compare(ON_EXIT) == 0) return;

			_scripts.erase(name);
			_scriptStatus.erase(name);
		}

		void ScriptingContext::addData(std::wstring name, std::wstring data)
		{
			if (name.compare(L"") == 0) return;
			_data.insert(name, data);
		}

		std::wstring ScriptingContext::getData(std::wstring name)
		{
			if (name.compare(L"") == 0) return L"";

			std::wstring data;
			if (_scripts.get(name, data))
			{
				return data;
			}
			return L"";
		}

		void ScriptingContext::removeData(std::wstring name)
		{
			if (name.compare(L"") == 0) return;
			_data.erase(name);
		}

		std::vector<std::pair<std::wstring, std::wstring>> ScriptingContext::getScripts()
		{
			std::vector<std::pair<std::wstring, std::wstring>> scripts;
			for (auto kv : _scripts.getData()) {
				scripts.push_back(kv);
			}
			return scripts;
		}

		void ScriptingContext::flagScript(std::wstring name)
		{
			if (name.compare(L"") == 0) return;
			_scriptStatus.insert(name, { false, UNSPECIFIED_ERROR });
		}

		void ScriptingContext::flagScript(std::wstring name, std::wstring error)
		{
			if (name.compare(L"") == 0) return;
			_scriptStatus.insert(name, { false, error });
		}

		void ScriptingContext::unflagScript(std::wstring name)
		{
			if (name.compare(L"") == 0) return;
			_scriptStatus.insert(name, { true, L"" });
		}

		bool ScriptingContext::getScriptStatus(std::wstring name)
		{
			if (name.compare(L"") == 0) return false;

			std::pair<bool, std::wstring> status;
			if (_scriptStatus.get(name, status))
			{
				return status.first;
			}
			return false;
		}

		std::wstring ScriptingContext::getScriptErrorMessage(std::wstring name)
		{
			if (name.compare(L"") == 0) return L"";

			std::pair<bool, std::wstring> status;
			if (_scriptStatus.get(name, status))
			{
				return status.second;
			}
			return L"";
		}
	}
}