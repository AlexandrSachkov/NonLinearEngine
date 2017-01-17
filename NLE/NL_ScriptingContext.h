#ifndef NL_SCRIPTING_CONTEXT_H_
#define NL_SCRIPTING_CONTEXT_H_

#include "NL_ThreadLocal.h"
#include "NL_Map.h"
#include "NL_LuaCustomTypes.h"

#include "cereal\cereal.hpp"
#include "cereal/types/string.hpp"
#include "cereal/types/vector.hpp"
#include "LuaIntf.h"

#include <vector>

namespace NLE
{
	namespace SCRIPT
	{
		static const std::string ON_INIT = "onInit";
		static const std::string ON_UPDATE = "onUpdate";
		static const std::string ON_EXIT = "onExit";

		static const std::string UNSPECIFIED_ERROR = "Unspecified";

		class IScriptable;
		class ScriptingContext
		{
		public:
			ScriptingContext(IScriptable* parent);
			~ScriptingContext();

			void addScript(std::string name, std::string script);
			std::string getScript(std::string name);
			void removeScript(std::string name);

			void store(std::string name, double data);
			void store(std::string name, std::string data);
			void store(std::string name, LuaIntf::LuaRef data);

			bool load(std::string name, double& data);
			bool load(std::string name, std::string& data);
			bool load(std::string name, LuaIntf::LuaRef& data);
			
			void deleteNum(std::string name);	
			void deleteStr(std::string name);
			void deleteObj(std::string name);

			void flagScript(std::string name);
			void flagScript(std::string name, std::string error);
			bool getScriptStatus(std::string name);
			std::string getScriptErrorMessage(std::string name);
			void unflagScript(std::string name);
			IScriptable* getParent();
			void setParent(IScriptable* parent);

			std::vector<std::pair<std::string, std::string>> getScripts();

			template<class Archive>
			void save(Archive& archive) const
			{
				Map<std::string, std::string, REPLACE> scripts;
				for (auto kv : _scripts.getData())
				{
					scripts.insert(kv.first, kv.second);
				}				
				archive(CEREAL_NVP(scripts));
			}

			template<class Archive>
			void load(Archive& archive)
			{
				Map<std::string, std::string, REPLACE> scripts;
				archive(CEREAL_NVP(scripts));

				for (auto kv : scripts.getData())
				{
					_scripts.insert(kv.first, kv.second);
				}
			}

			static void attachBindings(LuaIntf::CppBindModule<LuaIntf::LuaBinding>& binding)
			{
				binding.beginClass<ScriptingContext>("ScriptingContext")
					.addFunction("addScript", &ScriptingContext::addScript)
					.addFunction("getScript", &ScriptingContext::getScript)
					.addFunction("removeScript", &ScriptingContext::removeScript)
					.addFunction("storeNum", static_cast<void(ScriptingContext::*)(std::string name, double data)>(&ScriptingContext::store))
					.addFunction("storeStr", static_cast<void(ScriptingContext::*)(std::string name, std::string data)>(&ScriptingContext::store))
					.addFunction("storeObj", static_cast<void(ScriptingContext::*)(std::string name, LuaIntf::LuaRef data)>(&ScriptingContext::store))
					.addFunction(
						"loadNum", 
						static_cast<bool(ScriptingContext::*)(std::string name, double& data)>(&ScriptingContext::load), 
						LUA_ARGS(std::string, LuaIntf::_out<double&>))
					.addFunction(
						"loadStr", 
						static_cast<bool(ScriptingContext::*)(std::string name, std::string& data)>(&ScriptingContext::load), 
						LUA_ARGS(std::string, LuaIntf::_out<std::string&>))
					.addFunction(
						"loadObj", 
						static_cast<bool(ScriptingContext::*)(std::string name, LuaIntf::LuaRef& data)>(&ScriptingContext::load), 
						LUA_ARGS(std::string, LuaIntf::_out<LuaIntf::LuaRef&>))
					.addFunction("deleteNum", &ScriptingContext::deleteNum)
					.addFunction("deleteStr", &ScriptingContext::deleteStr)
					.addFunction("deleteObj", &ScriptingContext::deleteObj)
					.endClass();
			}

		private:
			IScriptable* _parent;

			Map<std::string, std::string, REPLACE> _scripts;
			Map<std::string, std::pair<bool, std::string>, REPLACE> _scriptStatus;
			Map<std::string, double, REPLACE> _numericData;
			Map<std::string, std::string, REPLACE> _stringData;
			Map<std::string, LuaIntf::LuaRef, REPLACE> _objectData;
		};
	}
}

#endif