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
			addScript(ON_INIT, "");
			addScript(ON_UPDATE, "");
			addScript(ON_EXIT, "");
		}

		ScriptingContext::~ScriptingContext()
		{
		}

		void ScriptingContext::addScript(std::string name, std::string script)
		{
			if (name.compare("") == 0) return;
			_scripts.insert(name, script);
			_scriptStatus.insert(name, { true, ""});
		}

		std::string ScriptingContext::getScript(std::string name)
		{
			if (name.compare("") == 0) return "";

			std::string script;
			if (_scripts.get(name, script))
			{
				return script;
			}
			return "";
		}

		void ScriptingContext::removeScript(std::string name)
		{
			if (name.compare("") == 0) return;
			else if (name.compare(ON_INIT) == 0) return;
			else if (name.compare(ON_UPDATE) == 0) return;
			else if (name.compare(ON_EXIT) == 0) return;

			_scripts.erase(name);
			_scriptStatus.erase(name);
		}

		void ScriptingContext::store(std::string name, double data)
		{
			_numericData.insert(name, data);
		}

		void ScriptingContext::store(std::string name, std::string data)
		{
			_stringData.insert(name, data);
		}

		void ScriptingContext::store(std::string name, LuaIntf::LuaRef data)
		{
			_objectData.insert(name, data);
		}

		bool ScriptingContext::load(std::string name, double& data)
		{
			if (_numericData.get(name, data))
				return true;
			return false;
		}

		bool ScriptingContext::load(std::string name, std::string& data)
		{
			if (_stringData.get(name, data))
				return true;
			return false;
		}

		bool ScriptingContext::load(std::string name, LuaIntf::LuaRef& data)
		{
			if (_objectData.get(name, data))
				return true;
			return false;
		}

		void ScriptingContext::deleteNum(std::string name)
		{
			_numericData.erase(name);
		}

		void ScriptingContext::deleteStr(std::string name)
		{
			_stringData.erase(name);
		}

		void ScriptingContext::deleteObj(std::string name)
		{
			_objectData.erase(name);
		}

		std::vector<std::pair<std::string, std::string>> ScriptingContext::getScripts()
		{
			std::vector<std::pair<std::string, std::string>> scripts;
			for (auto kv : _scripts.getData()) {
				scripts.push_back(kv);
			}
			return scripts;
		}

		void ScriptingContext::flagScript(std::string name)
		{
			if (name.compare("") == 0) return;
			_scriptStatus.insert(name, { false, UNSPECIFIED_ERROR });
		}

		void ScriptingContext::flagScript(std::string name, std::string error)
		{
			if (name.compare("") == 0) return;
			_scriptStatus.insert(name, { false, error });
		}

		void ScriptingContext::unflagScript(std::string name)
		{
			if (name.compare("") == 0) return;
			_scriptStatus.insert(name, { true, "" });
		}

		bool ScriptingContext::getScriptStatus(std::string name)
		{
			if (name.compare("") == 0) return false;

			std::pair<bool, std::string> status;
			if (_scriptStatus.get(name, status))
			{
				return status.first;
			}
			return false;
		}

		std::string ScriptingContext::getScriptErrorMessage(std::string name)
		{
			if (name.compare("") == 0) return "";

			std::pair<bool, std::string> status;
			if (_scriptStatus.get(name, status))
			{
				return status.second;
			}
			return "";
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