#pragma once

#include "NL_ThreadLocal.h"
#include "NL_LuaCustomTypes.h"
#include "NL_Pointer.h"

#include "cereal\cereal.hpp"
#include "cereal/types/string.hpp"
#include "cereal/types/vector.hpp"
#include "cereal/types/unordered_map.hpp"
#include "LuaIntf.h"

#include <vector>

namespace NLE
{
	namespace SCRIPT
	{
		struct ScriptingContextDesc {
			std::unordered_map<std::string, std::string> scripts;
			std::unordered_map<std::string, double> numericData;
			std::unordered_map<std::string, std::string> stringData;

			template<class Archive>
			void save(Archive& archive) const
			{
				archive(
					CEREAL_NVP(scripts),
					CEREAL_NVP(numericData),
					CEREAL_NVP(stringData)
					);
			}

			template<class Archive>
			void load(Archive& archive)
			{
				archive(
					CEREAL_NVP(scripts),
					CEREAL_NVP(numericData),
					CEREAL_NVP(stringData)
					);
			};

			static void attachMasterBindings(LuaIntf::CppBindModule<LuaIntf::LuaBinding>& binding)
			{
				binding.beginClass<ScriptingContextDesc>("ScriptingContextDesc")
					.addConstructor(LUA_ARGS())
					.endClass();
			}
		};

		static const std::string ON_INIT = "onInit";
		static const std::string ON_UPDATE = "onUpdate";
		static const std::string ON_EXIT = "onExit";

		static const std::string UNSPECIFIED_ERROR = "Unspecified";

		class IScriptable;
		class ScriptingContext
		{
		public:
			ScriptingContext(const ScriptingContextDesc&);
			ScriptingContext(const ScriptingContext&);
			ScriptingContext& operator=(const ScriptingContext&);
			~ScriptingContext();

			ScriptingContextDesc getDesc();

			bool addScript(std::string name, std::string script);
			bool getScript(std::string name, std::string& script);
			void removeScript(std::string name);

			bool store(std::string name, double data);
			bool store(std::string name, std::string data);

			bool load(std::string name, double& data);
			bool load(std::string name, std::string& data);
			
			void deleteNum(std::string name);	
			void deleteStr(std::string name);

			bool flagScript(std::string name);
			bool flagScript(std::string name, std::string error);
			bool getScriptStatus(std::string name, bool& status, std::string& error);
			bool unflagScript(std::string name);

			static void attachBindings(LuaIntf::CppBindModule<LuaIntf::LuaBinding>& binding)
			{
				binding.beginClass<ScriptingContext>("ScriptingContext")
					.addFunction("addScript", &ScriptingContext::addScript)
					.addFunction("getScript", &ScriptingContext::getScript, LUA_ARGS(std::string, LuaIntf::_out<std::string&>))
					.addFunction("removeScript", &ScriptingContext::removeScript)
					.addFunction("storeNum", static_cast<bool(ScriptingContext::*)(std::string name, double data)>(&ScriptingContext::store))
					.addFunction("storeStr", static_cast<bool(ScriptingContext::*)(std::string name, std::string data)>(&ScriptingContext::store))
					.addFunction(
						"loadNum", 
						static_cast<bool(ScriptingContext::*)(std::string name, double& data)>(&ScriptingContext::load), 
						LUA_ARGS(std::string, LuaIntf::_out<double&>))
					.addFunction(
						"loadStr", 
						static_cast<bool(ScriptingContext::*)(std::string name, std::string& data)>(&ScriptingContext::load), 
						LUA_ARGS(std::string, LuaIntf::_out<std::string&>))
					.addFunction("deleteNum", &ScriptingContext::deleteNum)
					.addFunction("deleteStr", &ScriptingContext::deleteStr)
					.endClass();
			}

			static void attachMasterBindings(LuaIntf::CppBindModule<LuaIntf::LuaBinding>& binding)
			{
				binding.beginClass<ScriptingContextDesc>("ScriptingContextDesc")
					.addConstructor(LUA_ARGS())
					.endClass();

				binding.beginClass<ScriptingContext>("ScriptingContext")
					.addConstructor(LUA_ARGS(const ScriptingContextDesc&))
					.endClass();
			}

		private:
			std::unordered_map<std::string, std::string> _scripts;
			std::unordered_map<std::string, std::pair<bool, std::string>> _scriptStatus;
			std::unordered_map<std::string, double> _numericData;
			std::unordered_map<std::string, std::string> _stringData;
		};
	}
}