#ifndef NL_GAME_H_
#define NL_GAME_H_

#include "NL_ScriptingContext.h"
#include "NL_ThreadLocal.h"

#include <string>
#include "cereal\cereal.hpp"
#include "cereal/types/string.hpp"

namespace NLE
{
	namespace GAME
	{
		class Game
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
					CEREAL_NVP(_testNum),
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
					CEREAL_NVP(_testNum),
					CEREAL_NVP(name),
					CEREAL_NVP(initialScene),
					CEREAL_NVP(_scriptingContext)
					);

				_name = cnv.from_bytes(name);
				_initialScene = cnv.from_bytes(initialScene);
			}

			void setName(std::wstring name);
			std::wstring getName();

			void setInitialScene(std::wstring sceneName);
			std::wstring getInitialScene();
			SCRIPT::ScriptingContext& getScriptingContext();

		private:
			unsigned long long _testNum;
			std::wstring _name;
			std::wstring _initialScene;
			SCRIPT::ScriptingContext _scriptingContext;
		};
	}
}

#endif