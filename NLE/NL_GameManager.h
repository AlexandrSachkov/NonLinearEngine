#ifndef NL_GAME_MANAGER_H_
#define NL_GAME_MANAGER_H_

#include "NL_IGameManager.h"
#include "NL_ISerializer.h"
#include "NL_OperationBuffer.h"

#include <functional>

namespace NLE
{
	class IWindowManager;
	class EngineServices;
	namespace GRAPHICS
	{
		class IRenderingEngine;
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
		class GameObject;
		
		class GameManager : public IGameManager
		{
		public:
			GameManager(
				EngineServices& eServices,
				IWindowManager& windowManager,
				IO::IFileIOManager* file,
				SERIALIZATION::ISerializer& serializer,
				GRAPHICS::IRenderingEngine* const renderingEngine,
				SCRIPT::IScriptingEngine* const scriptingEngine);
			~GameManager();

			void update(SystemServices* sServices, double deltaT);
			bool hasUnsavedChanges();
			void quitGame();
			ExecStatus getExecutionStatus();

		private:
			ExecStatus _execStatus;

			EngineServices& _eServices;
			IWindowManager& _windowManager;
			IO::IFileIOManager* _file;
			SERIALIZATION::ISerializer& _serializer;
			GRAPHICS::IRenderingEngine* const _renderingEngine;
			SCRIPT::IScriptingEngine* const _scriptingEngine;

			OperationBuffer _opBuffer;

			Game* _game;
			Scene* _currentScene;
		};
	}

}


#endif