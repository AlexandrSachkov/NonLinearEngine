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
		static const std::wstring ON_INIT = L"onInit";
		static const std::wstring ON_UPDATE = L"onUpdate";
		static const std::wstring ON_EXIT = L"onExit";

		static const std::wstring UNSPECIFIED_ERROR = L"Unspecified";

		class IScriptable;
		class ScriptingContext
		{
		public:
			ScriptingContext(IScriptable* parent);
			~ScriptingContext();

			void addScript(std::wstring name, std::wstring script);
			std::wstring getScript(std::wstring name);
			void removeScript(std::wstring name);

			void store(std::wstring name, double data);
			void store(std::wstring name, std::wstring data);
			void store(std::wstring name, LuaIntf::LuaRef data);

			bool load(std::wstring name, double& data);
			bool load(std::wstring name, std::wstring& data);
			bool load(std::wstring name, LuaIntf::LuaRef& data);
			
			void deleteNum(std::wstring name);	
			void deleteStr(std::wstring name);
			void deleteObj(std::wstring name);

			void flagScript(std::wstring name);
			void flagScript(std::wstring name, std::wstring error);
			bool getScriptStatus(std::wstring name);
			std::wstring getScriptErrorMessage(std::wstring name);
			void unflagScript(std::wstring name);
			IScriptable* getParent();
			void setParent(IScriptable* parent);

			std::vector<std::pair<std::wstring, std::wstring>> getScripts();

			template<class Archive>
			void save(Archive& archive) const
			{
				auto& cnv = TLS::strConverter.local();
				std::vector<std::string> scriptNames;
				std::string scriptName;
				std::string script;
				for (auto kv : _scripts.getData())
				{
					scriptName = cnv.to_bytes(kv.first);
					script = cnv.to_bytes(kv.second);
					scriptNames.push_back(scriptName);
					archive(cereal::make_nvp(scriptName, script));
				}				
				archive(CEREAL_NVP(scriptNames));
			}

			template<class Archive>
			void load(Archive& archive)
			{
				auto& cnv = TLS::strConverter.local();
				std::vector<std::string> scriptNames;
				archive(CEREAL_NVP(scriptNames));

				std::string script;
				for (auto scriptName : scriptNames)
				{
					archive(cereal::make_nvp(scriptName, script));
					_scripts.insert(cnv.from_bytes(scriptName), cnv.from_bytes(script));
				}
			}

			static void attachBindings(LuaIntf::CppBindModule<LuaIntf::LuaBinding>& binding)
			{
				binding.beginClass<ScriptingContext>("ScriptingContext")
					.addFunction("addScript", &ScriptingContext::addScript)
					.addFunction("getScript", &ScriptingContext::getScript)
					.addFunction("removeScript", &ScriptingContext::removeScript)
					.addFunction("storeNum", static_cast<void(ScriptingContext::*)(std::wstring name, double data)>(&ScriptingContext::store))
					.addFunction("storeStr", static_cast<void(ScriptingContext::*)(std::wstring name, std::wstring data)>(&ScriptingContext::store))
					.addFunction("storeObj", static_cast<void(ScriptingContext::*)(std::wstring name, LuaIntf::LuaRef data)>(&ScriptingContext::store))
					.addFunction(
						"loadNum", 
						static_cast<bool(ScriptingContext::*)(std::wstring name, double& data)>(&ScriptingContext::load), 
						LUA_ARGS(std::wstring, LuaIntf::_out<double&>))
					.addFunction(
						"loadStr", 
						static_cast<bool(ScriptingContext::*)(std::wstring name, std::wstring& data)>(&ScriptingContext::load), 
						LUA_ARGS(std::wstring, LuaIntf::_out<std::wstring&>))
					.addFunction(
						"loadObj", 
						static_cast<bool(ScriptingContext::*)(std::wstring name, LuaIntf::LuaRef& data)>(&ScriptingContext::load), 
						LUA_ARGS(std::wstring, LuaIntf::_out<LuaIntf::LuaRef&>))
					.addFunction("deleteNum", &ScriptingContext::deleteNum)
					.addFunction("deleteStr", &ScriptingContext::deleteStr)
					.addFunction("deleteObj", &ScriptingContext::deleteObj)
					.endClass();
			}

		private:
			IScriptable* _parent;

			Map<std::wstring, std::wstring, REPLACE> _scripts;
			Map<std::wstring, std::pair<bool, std::wstring>, REPLACE> _scriptStatus;
			Map<std::wstring, double, REPLACE> _numericData;
			Map<std::wstring, std::wstring, REPLACE> _stringData;
			Map<std::wstring, LuaIntf::LuaRef, REPLACE> _objectData;
		};
	}
}

#endif