#ifndef NL_GAME_H_
#define NL_GAME_H_

#include "NL_ScriptingContext.h"
#include "NL_ThreadLocal.h"
#include "NL_IScriptable.h"
#include "NL_LuaCustomTypes.h"
#include "NL_Map.h"
#include "NL_IConsoleQueue.h"

#include <string>
#include "cereal\cereal.hpp"
#include "cereal/types/string.hpp"

namespace NLE
{
	namespace GAME
	{
		class GameManager;
		class Game : virtual SCRIPT::IScriptable
		{
		public:
			Game();
			Game(GameManager* gameManager, CONSOLE::IConsoleQueue_EService* console);
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

				Map<std::string, std::string, REPLACE> scenes;
				for (auto kv : _scenes.getData())
				{
					scenes.insert(cnv.to_bytes(kv.first), cnv.to_bytes(kv.second));
				}
				archive(CEREAL_NVP(scenes));
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

				_scriptingContext.setParent(this);
				_name = cnv.from_bytes(name);
				_initialScene = cnv.from_bytes(initialScene);

				Map<std::string, std::string, REPLACE> scenes;
				archive(CEREAL_NVP(scenes));
				for (auto kv : scenes.getData())
				{
					_scenes.insert(cnv.from_bytes(kv.first), cnv.from_bytes(kv.second));
				}
			}

			GameManager* getGameManager();
			void setGameManager(GameManager& gameManager);
			void attachConsole(CONSOLE::IConsoleQueue_EService* console);

			void setName(std::wstring name);
			std::wstring getName();

			void setInitialScene(std::wstring sceneName);
			std::wstring getInitialScene();
			void addScene(std::wstring name, std::wstring path);
			void removeScene(std::wstring name);
			bool getScenePath(std::wstring name, std::wstring& path);
			std::vector<std::pair<std::wstring, std::wstring>> getScenes();
			SCRIPT::ScriptingContext& getScriptingContext();
			void bind(LuaIntf::CppBindModule<LuaIntf::LuaBinding>& binding);

			static void attachBindings(LuaIntf::CppBindModule<LuaIntf::LuaBinding>& binding)
			{
				binding.beginClass<Game>("Game")
					.addProperty("name", &Game::getName, &Game::setName)
					.addFunction("getGameManager", &Game::getGameManager)
					.addFunction("getScriptingContext", &Game::getScriptingContext)
					.endClass();
			}

		private:
			CONSOLE::IConsoleQueue_EService* _console;
			GameManager* _gameManager;
			std::wstring _name;
			std::wstring _initialScene;
			SCRIPT::ScriptingContext _scriptingContext;
			Map<std::wstring, std::wstring, REPLACE> _scenes;
		};
	}
}

#endif