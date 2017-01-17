#ifndef NL_GAME_H_
#define NL_GAME_H_

#include "NL_ScriptingContext.h"
#include "NL_ThreadLocal.h"
#include "NL_IScriptable.h"
#include "NL_LuaCustomTypes.h"
#include "NL_Map.h"
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
		class GameManager;
		class Game : virtual SCRIPT::IScriptable
		{
		public:
			Game();
			Game(CONSOLE::IConsoleQueue_EServiceSP console);
			~Game();

			template<class Archive>
			void save(Archive& archive) const
			{
				archive(
					CEREAL_NVP(_name),
					CEREAL_NVP(_initialScene),
					CEREAL_NVP(_scriptingContext)
					);

				Map<std::string, std::string, REPLACE> scenes;
				for (auto kv : _scenes.getData())
				{
					scenes.insert(kv.first, kv.second);
				}
				archive(CEREAL_NVP(scenes));
			}

			template<class Archive>
			void load(Archive& archive)
			{
				archive(
					CEREAL_NVP(_name),
					CEREAL_NVP(_initialScene),
					CEREAL_NVP(_scriptingContext)
					);

				Map<std::string, std::string, REPLACE> scenes;
				archive(CEREAL_NVP(scenes));
				for (auto kv : scenes.getData())
				{
					_scenes.insert(kv.first, kv.second);
				}
			}

			void attachConsole(CONSOLE::IConsoleQueue_EServiceSP console);

			void setName(std::string name);
			std::string getName();

			void setInitialScene(std::string sceneName);
			std::string getInitialScene();
			void addScene(std::string name, std::string path);
			void removeScene(std::string name);
			std::string getScenePath(std::string name);
			std::unordered_map<std::string, std::string> getScenes();
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
					.addFunction("setInitialScene", &Game::setInitialScene)
					.addFunction("getInitialScene", &Game::getInitialScene)
					.addFunction("addScene", &Game::addScene)
					.addFunction("removeScene", &Game::removeScene)
					.addFunction("getScenes", &Game::getScenes)
					.addFunction("getScenePath", &Game::getScenePath)
					.endClass();
			}

		private:
			CONSOLE::IConsoleQueue_EServiceSP _console;
			std::string _name;
			std::string _initialScene;
			SCRIPT::ScriptingContext _scriptingContext;
			Map<std::string, std::string, REPLACE> _scenes;
		};

		typedef std::unique_ptr<Game> GameUP;
	}
}

#endif