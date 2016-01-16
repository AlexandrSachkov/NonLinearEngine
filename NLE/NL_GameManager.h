#ifndef NL_GAME_MANAGER_H_
#define NL_GAME_MANAGER_H_

#include "NL_IGameManager.h"
#include "NL_System.h"
#include "NL_SysInitializer.h"

#include <functional>

#include "tbb\atomic.h"

struct lua_State;
namespace NLE
{
	namespace GRAPHICS
	{
		class Scene;
	}


	struct GameManagerInitializer : public Core::SysInitializer
	{
		GameManagerInitializer() :
			gamePath(L"")
		{
		}

		std::wstring gamePath;
	};

	class GameManager : public Core::System, public IGameManager
	{
	public:
		GameManager();
		~GameManager();

		bool initialize(std::unique_ptr<Core::SysInitializer> const& initializer);
		void start();
		void stop();
		void release();

		bool initialized();
		std::function<void()> const& getExecutionProcedure();
		Core::ISystem& getInterface();

	private:
		bool _initialized;
		std::function<void()> _procedure;

	};
}


#endif