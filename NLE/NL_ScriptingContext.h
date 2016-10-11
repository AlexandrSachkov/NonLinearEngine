#ifndef NL_SCRIPTING_CONTEXT_H_
#define NL_SCRIPTING_CONTEXT_H_

#include "NL_ThreadLocal.h"
#include "NL_Map.h"

#include "cereal\cereal.hpp"
#include "cereal/types/string.hpp"
#include "cereal/types/vector.hpp"

#include <vector>

namespace NLE
{
	namespace SCRIPT
	{
		static const std::wstring ON_INIT = L"onInit";
		static const std::wstring ON_UPDATE = L"onUpdate";
		static const std::wstring ON_EXIT = L"onExit";

		static const std::wstring UNSPECIFIED_ERROR = L"Unspecified";

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
			void flagScript(std::wstring name);
			void flagScript(std::wstring name, std::wstring error);
			bool getScriptStatus(std::wstring name);
			std::wstring getScriptErrorMessage(std::wstring name);
			void unflagScript(std::wstring name);

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

		private:
			Map<std::wstring, std::wstring, REPLACE> _scripts;
			Map<std::wstring, std::pair<bool, std::wstring>, REPLACE> _scriptStatus;
			Map<std::wstring, std::wstring, REPLACE> _data;
		};
	}
}

#endif