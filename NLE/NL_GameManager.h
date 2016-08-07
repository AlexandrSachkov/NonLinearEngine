#ifndef NL_GAME_MANAGER_H_
#define NL_GAME_MANAGER_H_

#include "NL_IGameManager.h"
#include "NL_EngineServices.h"
#include "NL_Serializer.h"
#include "NL_CommandBuffer.h"

#include <functional>

namespace NLE
{
	namespace GRAPHICS
	{
		class IRenderingEngine;
	}
	namespace UI
	{
		class IUiManager;
	}
	namespace SCRIPT
	{
		class IScriptingEngine;
	}
	namespace IO
	{
		class IFileIOManager;
	}
	namespace GAME
	{
		class Game;
		class Scene;
		class GameManager : public IGameManager
		{
		public:
			GameManager(
				EngineServices& eServices,
				IO::IFileIOManager* file,
				SERIALIZATION::Serializer& serializer,
				GRAPHICS::IRenderingEngine* const renderingEngine,
				UI::IUiManager* const uiManager,
				SCRIPT::IScriptingEngine* const scriptingEngine);
			~GameManager();

			void update(SystemServices* sServices, DataManager* data, double deltaT);
			void queueCommand(COMMAND::Type type, COMMAND::Data data);
			ExecStatus getExecutionStatus();

		private:
			ExecStatus _execStatus;

			EngineServices& _eServices;
			IO::IFileIOManager* _file;
			SERIALIZATION::Serializer& _serializer;
			GRAPHICS::IRenderingEngine* const _renderingEngine;
			UI::IUiManager* const _uiManager;
			SCRIPT::IScriptingEngine* const _scriptingEngine;

			CommandBuffer<COMMAND::Data> _commandBuffer;
			SERIALIZATION::Form _serializationForm;

			Game* _game;
			Scene* _currentScene;
		};
	}

}


#endif