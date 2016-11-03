#include "NL_ScriptingContext.h"
#include "NL_IScriptable.h"
#include "NL_ThreadLocal.h"

namespace NLE
{
	namespace SCRIPT
	{
		ScriptingContext::ScriptingContext(IScriptable* parent) :
			_parent(parent)
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

		void ScriptingContext::store(std::wstring name, double data)
		{
			_numericData.insert(name, data);
		}

		void ScriptingContext::store(std::wstring name, std::wstring data)
		{
			_stringData.insert(name, data);
		}

		void ScriptingContext::store(std::wstring name, LuaIntf::LuaRef data)
		{
			_objectData.insert(name, data);
		}

		bool ScriptingContext::load(std::wstring name, double& data)
		{
			if (_numericData.get(name, data))
				return true;
			return false;
		}

		bool ScriptingContext::load(std::wstring name, std::wstring& data)
		{
			if (_stringData.get(name, data))
				return true;
			return false;
		}

		bool ScriptingContext::load(std::wstring name, LuaIntf::LuaRef& data)
		{
			if (_objectData.get(name, data))
				return true;
			return false;
		}

		void ScriptingContext::deleteNum(std::wstring name)
		{
			_numericData.erase(name);
		}

		void ScriptingContext::deleteStr(std::wstring name)
		{
			_stringData.erase(name);
		}

		void ScriptingContext::deleteObj(std::wstring name)
		{
			_objectData.erase(name);
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

		IScriptable* ScriptingContext::getParent()
		{
			return _parent;
		}

		void ScriptingContext::setParent(IScriptable* parent)
		{
			_parent = parent;
		}
	}
}