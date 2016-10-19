#ifndef NL_GAME_H_
#define NL_GAME_H_

#include "NL_ScriptingContext.h"
#include "NL_ThreadLocal.h"
#include "NL_IScriptable.h"
#include "NL_LuaCustomTypes.h"

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
			Game(GameManager* gameManager);
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

				_scriptingContext.setParent(this);
				_name = cnv.from_bytes(name);
				_initialScene = cnv.from_bytes(initialScene);
			}

			GameManager* getGameManager();
			void setGameManager(GameManager& gameManager);

			void setName(std::wstring name);
			std::wstring getName();

			void setInitialScene(std::wstring sceneName);
			std::wstring getInitialScene();
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
			GameManager* _gameManager;
			std::wstring _name;
			std::wstring _initialScene;
			SCRIPT::ScriptingContext _scriptingContext;
		};
	}
}

#endif