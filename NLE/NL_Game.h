#pragma once

#include "NL_ScriptingContext.h"
#include "NL_ThreadLocal.h"
#include "NL_IScriptable.h"
#include "NL_LuaCustomTypes.h"
#include "NL_IConsoleQueue.h"
#include "NL_IGameManager.h"

#include <string>
#include "cereal\cereal.hpp"
#include "cereal/types/string.hpp"
#include <memory>

namespace NLE
{
	namespace GAME
	{
		struct GameDesc {
			std::string name;
			SCRIPT::ScriptingContextDesc scriptingContextDesc;

			template<class Archive>
			void save(Archive& archive) const
			{
				archive(
					CEREAL_NVP(name),
					CEREAL_NVP(scriptingContextDesc)
					);
			}

			template<class Archive>
			void load(Archive& archive)
			{
				archive(
					CEREAL_NVP(name),
					CEREAL_NVP(scriptingContextDesc)
					);
			};

			void setName(std::string nameVal)
			{
				name = nameVal;
			}

			std::string getName()
			{
				return name;
			}

			static void attachMasterBindings(LuaIntf::CppBindModule<LuaIntf::LuaBinding>& binding)
			{
				binding.beginClass<GameDesc>("GameDesc")
					.addConstructor(LUA_ARGS())
					.addProperty("name", &GameDesc::getName, &GameDesc::setName)
					.endClass();
			}
		};

		class GameManager;
		class Game : virtual SCRIPT::IScriptable
		{
		public:
			Game(CONSOLE::IConsoleQueue_EServiceSP, const GameDesc&);
			Game(const Game&);
			Game& operator=(const Game&);
			~Game();

			GameDesc getDesc();

			void setName(std::string name);
			std::string getName();

			SCRIPT::ScriptingContext& getScriptingContext();
			void bind(LuaIntf::CppBindModule<LuaIntf::LuaBinding>& binding);

			static void attachBindings(LuaIntf::CppBindModule<LuaIntf::LuaBinding>& binding)
			{
				binding.beginClass<Game>("Game")
					.addFunction("getName", &Game::getName)
					.addFunction("getScriptingContext", &Game::getScriptingContext)
					.endClass();
			}

			static void attachMasterBindings(LuaIntf::CppBindModule<LuaIntf::LuaBinding>& binding)
			{
				binding.beginClass<Game>("Game")
					.addFunction("setName", &Game::setName)
					.endClass();
			}

		private:
			CONSOLE::IConsoleQueue_EServiceSP _console;
			std::string _name;
			SCRIPT::ScriptingContext _scriptingContext;
		};

		typedef std::unique_ptr<Game> GameUP;
	}
}
