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

		/*void ScriptingContext::addData(std::wstring name, std::wstring data)
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
		}*/

		void ScriptingContext::store(std::wstring name, double data)
		{
			_data.insert(name, new double(data));
		}

		void ScriptingContext::store(std::wstring name, std::wstring data)
		{
			_data.insert(name, new std::wstring(data));
		}

		void ScriptingContext::store(std::wstring name, LuaIntf::LuaRef data)
		{
			_data.insert(name, new LuaIntf::LuaRef(data));
		}

		double ScriptingContext::loadNum(std::wstring name)
		{
			void* val;
			_data.get(name, val);
			return *static_cast<double*>(val);
		}

		std::wstring ScriptingContext::loadStr(std::wstring name)
		{
			void* val;
			_data.get(name, val);
			return *static_cast<std::wstring*>(val);
		}

		LuaIntf::LuaRef ScriptingContext::loadObj(std::wstring name)
		{
			void* val;
			_data.get(name, val);
			return *static_cast<LuaIntf::LuaRef*>(val);
		}

		void ScriptingContext::deleteNum(std::wstring name)
		{
			void* data;
			if (_data.get(name, data))
			{
				delete (double*)data;
				_data.erase(name);
			}
		}

		void ScriptingContext::deleteStr(std::wstring name)
		{
			void* data;
			if (_data.get(name, data))
			{
				delete (std::wstring*)data;
				_data.erase(name);
			}
		}

		void ScriptingContext::deleteObj(std::wstring name)
		{
			void* data;
			if (_data.get(name, data))
			{
				delete (LuaIntf::LuaRef*)data;
				_data.erase(name);
			}
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