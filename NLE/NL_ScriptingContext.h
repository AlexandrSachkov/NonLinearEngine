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

			double loadNum(std::wstring name);
			std::wstring loadStr(std::wstring name);
			LuaIntf::LuaRef loadObj(std::wstring name);
			
			void deleteNum(std::wstring name);	
			void deleteStr(std::wstring name);
			void deleteObj(std::wstring name);
			/*
			void store(std::string name, bool data);
			void store(std::string name, LuaIntf::LuaRef data);
			void store(std::string name, const std::vector<std::string>& data);
			void store(std::string name, std::map<std::string, int>& data);*/

			

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
					.addFunction("loadNum", &ScriptingContext::loadNum)
					.addFunction("loadStr", &ScriptingContext::loadStr)
					.addFunction("loadObj", &ScriptingContext::loadObj)
					.addFunction("deleteNum", &ScriptingContext::deleteNum)
					.addFunction("deleteStr", &ScriptingContext::deleteStr)
					.addFunction("deleteObj", &ScriptingContext::deleteObj)
					.endClass();
			}

		private:
			IScriptable* _parent;

			Map<std::wstring, std::wstring, REPLACE> _scripts;
			Map<std::wstring, std::pair<bool, std::wstring>, REPLACE> _scriptStatus;
			Map<std::wstring, void*, REPLACE> _data;
		};
	}
}

#endif