#ifndef NL_GAME_H_
#define NL_GAME_H_

#include "NL_ScriptingContext.h"
#include "NL_ThreadLocal.h"
#include "NL_IScriptable.h"

#include <string>
#include "cereal\cereal.hpp"
#include "cereal/types/string.hpp"

namespace NLE
{
	namespace GAME
	{
		class Game : virtual SCRIPT::IScriptable
		{
		public:
			Game();
			~Game();

			template<class Archive>
			void save(Archive& archive) const
			{
				auto& cnv = TLS::strConverter.local();
				auto name = cnv.to_bytes(_name);
				auto initialScene = cnv.to_bytes(_initialScene);
				archive(
					CEREAL_NVP(name),
					CEREAL_NVP(initialScene),
					CEREAL_NVP(_scriptingContext)
					);
			}

			template<class Archive>
			void load(Archive& archive)
			{
				auto& cnv = TLS::strConverter.local();
				std::string name;
				std::string initialScene;
				archive(
					CEREAL_NVP(name),
					CEREAL_NVP(initialScene),
					CEREAL_NVP(_scriptingContext)
					);

				_name = cnv.from_bytes(name);
				_initialScene = cnv.from_bytes(initialScene);
			}

			void setName(std::wstring name);
			void setName(std::string name);
			std::wstring getName();
			std::string getNameStr();

			void setInitialScene(std::wstring sceneName);
			std::wstring getInitialScene();
			SCRIPT::ScriptingContext& getScriptingContext();
			void bind(LuaIntf::CppBindModule<LuaIntf::LuaBinding>& binding);

			static void attachBindings(LuaIntf::CppBindModule<LuaIntf::LuaBinding>& binding)
			{
				binding.beginClass<Game>("Game")
					.addProperty("name", &Game::getNameStr, static_cast<void(Game::*)(std::string)>(&Game::setName))
					.addFunction("getScriptingContext", &Game::getScriptingContext)
					.endClass();
			}

		private:
			std::wstring _name;
			std::wstring _initialScene;
			SCRIPT::ScriptingContext _scriptingContext;
		};
	}
}

#endif