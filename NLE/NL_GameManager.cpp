#include "NL_GameManager.h"
#include "NL_IRenderingEngine.h"
#include "NL_Systems.h"
#include "NL_DeviceCore.h"
#include "NL_Console.h"
#include "NL_ThreadLocal.h"
#include "NL_SysInitializer.h"

#include <assert.h>

namespace NLE
{
	GameManager::GameManager() :
		_initialized(false),
		_procedure(nullptr)
	{

	}

	GameManager::~GameManager()
	{

	}

	bool GameManager::initialize(std::unique_ptr<Core::SysInitializer> const& initializer)
	{
		assert(!_initialized);

		_procedure = [&](){
			//load and unload objects as necessary
		};
		_initialized = true;
		return true;
	}

	void GameManager::start()
	{

	}

	void GameManager::stop()
	{

	}

	void GameManager::release()
	{
		_initialized = false;
	}

	bool GameManager::initialized()
	{
		return _initialized;
	}

	std::function<void()> const& GameManager::getExecutionProcedure()
	{
		return _procedure;
	}

	Core::ISystem& GameManager::getInterface()
	{
		return *this;
	}
}