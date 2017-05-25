#include "NL_ScriptingContext.h"
#include "NL_IScriptable.h"
#include "NL_ThreadLocal.h"

namespace NLE
{
	namespace SCRIPT
	{
		ScriptingContext::ScriptingContext(const ScriptingContextDesc& desc)
		{
			addScript(ON_INIT, "");
			addScript(ON_UPDATE, "");
			addScript(ON_EXIT, "");

			for (auto kv : desc.scripts)
			{
				addScript(kv.first, kv.second);
			}
			for (auto kv : desc.numericData)
			{
				store(kv.first, kv.second);
			}
			for (auto kv : desc.stringData)
			{
				store(kv.first, kv.second);
			}
		}

		ScriptingContext::ScriptingContext(const ScriptingContext& other) :
			_scripts(other._scripts),
			_numericData(other._numericData),
			_stringData(other._stringData)
		{
		}

		ScriptingContext& ScriptingContext::operator=(const ScriptingContext& other)
		{
			_scripts = other._scripts;
			_numericData = other._numericData;
			_stringData = other._stringData;
			return *this;
		}

		ScriptingContext::~ScriptingContext()
		{
		}

		ScriptingContextDesc ScriptingContext::getDesc()
		{
			ScriptingContextDesc desc;
			desc.scripts = _scripts;
			desc.numericData = _numericData;
			desc.stringData = _stringData;
			return desc;
		}

		bool ScriptingContext::addScript(std::string name, std::string script)
		{
			if (name.empty()) 
				return false;

			auto it = _scripts.find(name);
			if (it != _scripts.end()) //already exists
			{
				_scripts.erase(it);
				_scriptStatus.erase(name);
			}
			_scripts.insert({ name, script });
			_scriptStatus.insert({ name, { true, ""} });
			return true;
		}

		bool ScriptingContext::getScript(std::string name, std::string& script)
		{
			if (name.empty()) 
				return false;

			auto it = _scripts.find(name);
			if (it != _scripts.end())
			{
				script = it->second;
				return true;
			}
			return false;
		}

		void ScriptingContext::removeScript(std::string name)
		{
			if (name.empty()
				|| name.compare(ON_INIT) == 0
				|| name.compare(ON_UPDATE) == 0
				||name.compare(ON_EXIT) == 0) 
				return;

			_scripts.erase(name);
			_scriptStatus.erase(name);
		}

		bool ScriptingContext::store(std::string name, double data)
		{
			if (name.empty())
				return false;

			auto it = _numericData.find(name);
			if (it != _numericData.end()) //already exists
			{
				_numericData.erase(it);
			}
			_numericData.insert({ name, data });
			return true;
		}

		bool ScriptingContext::store(std::string name, std::string data)
		{
			if (name.empty())
				return false;

			auto it = _stringData.find(name);
			if (it != _stringData.end()) //already exists
			{
				_stringData.erase(it);
			}

			_stringData.insert({ name, data });
			return true;
		}

		bool ScriptingContext::load(std::string name, double& data)
		{
			if (name.empty())
				return false;

			auto it = _numericData.find(name);
			if (it != _numericData.end())
			{
				data = it->second;
				return true;
			}
			return false;
		}

		bool ScriptingContext::load(std::string name, std::string& data)
		{
			if (name.empty())
				return false;

			auto it = _stringData.find(name);
			if (it != _stringData.end())
			{
				data = it->second;
				return true;
			}
			return false;
		}

		void ScriptingContext::deleteNum(std::string name)
		{
			if (name.empty())
				return;

			_numericData.erase(name);
		}

		void ScriptingContext::deleteStr(std::string name)
		{
			if (name.empty())
				return;

			_stringData.erase(name);
		}

		bool ScriptingContext::flagScript(std::string name)
		{
			if (name.empty())
				return false;

			_scriptStatus.insert({ name, { false, UNSPECIFIED_ERROR } });
			return true;
		}

		bool ScriptingContext::flagScript(std::string name, std::string error)
		{
			if (name.empty())
				return false;

			_scriptStatus.insert({ name, { false, error } });
			return true;
		}

		bool ScriptingContext::unflagScript(std::string name)
		{
			if (name.empty())
				return false;

			_scriptStatus.insert({ name, { true, "" } });
			return true;
		}

		bool ScriptingContext::getScriptStatus(std::string name, bool& status, std::string& err)
		{
			if (name.empty())
				return false;

			auto it = _scriptStatus.find(name);
			if (it != _scriptStatus.end())
			{
				auto statusErr = it->second;
				status = statusErr.first;
				err = statusErr.second;
				return true;
			}
			return false;
		}
	}
}