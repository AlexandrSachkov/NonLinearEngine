#include "NL_Nle.h"

#include "NL_ThreadLocal.h"
#include "NL_DeviceCore.h"
#include "NL_ExecutionDesc.h"
#include "NL_InputEvents.h"
#include "NL_InputProcessor.h"
#include "NL_GameManager.h"
#include "NL_Systems.h"
#include "NL_Console.h"
#include "NL_UiManager.h"
#include "NL_RenderingEngine.h"
#include "NL_WindowManager.h"
#include "NL_FileIOManager.h"

#include "lua.hpp"

#include <assert.h>
#include <memory>
#include <locale>
#include <codecvt>
#include <thread>
#include <chrono>


namespace NLE
{
	Nle* Nle::_nle = nullptr;

	Nle::Nle() :
		_initialized(false),
		_defaultGrainSize(6500)
	{
		_running.store(false);

		Core::DeviceCore& core = Core::DeviceCore::instance();

		Core::ExecutionDesc uiManagerProcDesc(
			Core::Priority::LOW,
			Core::Execution::RECURRING,
			Core::Mode::SYNC,
			Core::Startup::AUTOMATIC,
			33333333L	//30 FPS
			);
		core.attachSystem(SYS::SYS_UI_MANAGER, uiManagerProcDesc, std::unique_ptr<UI::UiManager>(new UI::UiManager()));

		Core::ExecutionDesc inputProcDesc(
			Core::Priority::STANDARD,
			Core::Execution::RECURRING,
			Core::Mode::ASYNC,
			Core::Startup::AUTOMATIC,
			16666666L	//60 FPS
			);
		core.attachSystem(SYS::SYS_INPUT_PROCESSOR, inputProcDesc, std::unique_ptr<INPUT::InputProcessor>(new INPUT::InputProcessor()));

		Core::ExecutionDesc renderingEngineProcDesc(
			Core::Priority::STANDARD,
			Core::Execution::SINGULAR,
			Core::Mode::ASYNC,
			Core::Startup::AUTOMATIC,
			0L
			//16393443L
			//16666666L	//60 FPS		
			);
		core.attachSystem(SYS::SYS_RENDERING_ENGINE, renderingEngineProcDesc, std::unique_ptr<GRAPHICS::RenderingEngine>(new GRAPHICS::RenderingEngine()));

		Core::ExecutionDesc gameMngrProcDesc(
			Core::Priority::STANDARD,
			Core::Execution::RECURRING,
			Core::Mode::ASYNC,
			Core::Startup::AUTOMATIC,
			33333333L	//30 FPS
			);
		core.attachSystem(SYS::SYS_GAME_MANAGER, gameMngrProcDesc, std::unique_ptr<GameManager>(new GameManager()));
	}

	Nle::~Nle()
	{
	}

	bool Nle::initialize(Size2D screenSize, bool fullscreen, bool decorated, std::wstring title)
	{
		assert(!_initialized);

		std::unique_ptr<GRAPHICS::Initializer> renderingEngineInit = std::make_unique<GRAPHICS::Initializer>();
		renderingEngineInit->screenSize = screenSize;
		renderingEngineInit->fullscreen = fullscreen;
		renderingEngineInit->decorated = decorated;
		renderingEngineInit->title = title;
		renderingEngineInit->openglMajorVersion = 4;
		renderingEngineInit->openglMinorVersion = 5;
		Core::DeviceCore::instance().setSystemInitializer(SYS::SYS_RENDERING_ENGINE, std::move(renderingEngineInit));

		if (!Core::DeviceCore::instance().initialize())
			return false;

		_initialized = true;
		CONSOLE::out(CONSOLE::STANDARD, L"NLE successfully initialized.");

		return true;
	}

	void Nle::release()
	{
		if (!_initialized)
			return;

		Core::DeviceCore::instance().release();
		_initialized = false;
		CONSOLE::out(CONSOLE::STANDARD, L"NLE released.");

		CONSOLE::Console::instance().outputConsole(); //output all the remaining console data after UiManager has been released
		CONSOLE::Console::instance().release();

		delete this;
	}

	void Nle::run()
	{
		assert(_initialized);
		_running.store(true);
		Core::DeviceCore::instance().run();
	}

	void Nle::stop()
	{
		Core::DeviceCore::instance().stop();
		_running.store(false);
	}
}

int main(void)
{
	NLE::Nle& nle = NLE::Nle::instance();
	nle.initialize(NLE::Size2D(800, 600), false, true, L"NonLinear Engine");
	nle.run();
	nle.release();
	return 0;
}

