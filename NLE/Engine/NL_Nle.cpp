#include "NL_Nle.h"

#include "NL_ThreadLocal.h"
#include "NLCore\NL_DeviceCore.h"
#include "NLCore\NL_ExecutionDesc.h"
#include "NL_InputEvents.h"
#include "NL_InputProcessor.h"
#include "NL_SceneManager.h"
#include "NL_CameraManager.h"
#include "NL_Systems.h"
#include "NL_SharedContainers.h"
#include "NL_Console.h"
#include "NL_UiManager.h"
#include "NL_RenderingEngine.h"

#include "lua.hpp"
#include "tbb\spin_mutex.h"

#include <assert.h>
#include <memory>
#include <locale>
#include <codecvt>
#include <thread>
#include <chrono>
#include "DirectXMath.h"

namespace NLE
{
	Nle* Nle::_nle = nullptr;

	Nle::Nle() :
		_initialized(false),
		_running(false),
		_defaultGrainSize(6500)
	{
		_runningLock = new tbb::spin_mutex();

		Core::DeviceCore& core = Core::DeviceCore::instance();
		core.setClockPeriodNs(1000000L);

		// Install shared containers
		core.installSContainer<char>(CAMERA_COMMANDS, GRAPHICS::COMMANDS::CAMERA::NUM_COMMANDS, _defaultGrainSize); //one slot for each command
		core.installSContainer<double>(CURSOR_COORDINATES, 2, _defaultGrainSize);	// 2 slots for x and y components
		core.installSContainer<double>(SCROLL_OFFSET, 2, _defaultGrainSize);	// 2 slots for x and y components
		core.installSContainer<DirectX::XMFLOAT4X4>(VIEW_PROJECTION_MATRIX, 1, _defaultGrainSize);
		core.installSContainer<DirectX::XMFLOAT4>(EYE_VECTOR, 1, _defaultGrainSize);
		core.installSContainer<double>(FPS, 1, _defaultGrainSize);
		core.installSContainer<DirectX::XMFLOAT4>(CANVAS_BG_COLOR, 1, _defaultGrainSize);

		// Attach systems
		Core::ExecutionDesc uiManagerProcDesc(
			Core::Priority::LOW,
			Core::Execution::RECURRING,
			Core::Mode::SYNC,
			Core::Startup::AUTOMATIC,
			33333333L	//30 FPS
			);
		core.attachSystem(SYS::SYS_UI_MANAGER, uiManagerProcDesc, std::unique_ptr<UI::UiManager>(new UI::UiManager()));

		Core::ExecutionDesc inputProcDesc(
			Core::Priority::HIGH,
			Core::Execution::RECURRING,
			Core::Mode::SYNC,
			Core::Startup::AUTOMATIC,
			16666666L	//60 FPS
			);
		core.attachSystem(SYS::SYS_INPUT_PROCESSOR, inputProcDesc, std::unique_ptr<INPUT::InputProcessor>(new INPUT::InputProcessor()));

		Core::ExecutionDesc cameraMngrProcDesc(
			Core::Priority::STANDARD,
			Core::Execution::RECURRING,
			Core::Mode::ASYNC,
			Core::Startup::AUTOMATIC,
			16666666L	//60 FPS
			);
		core.attachSystem(SYS::SYS_CAMERA_MANAGER, cameraMngrProcDesc, std::unique_ptr<GRAPHICS::CameraManager>(new GRAPHICS::CameraManager()));

		Core::ExecutionDesc renderingEngineProcDesc(
			Core::Priority::STANDARD,
			Core::Execution::RECURRING,
			Core::Mode::ASYNC,
			Core::Startup::AUTOMATIC,
			14285714L	//70 FPS
			);
		core.attachSystem(SYS::SYS_RENDERING_ENGINE, renderingEngineProcDesc, std::unique_ptr<GRAPHICS::RenderingEngine>(new GRAPHICS::RenderingEngine()));

		Core::ExecutionDesc sceneMngrProcDesc(
			Core::Priority::STANDARD,
			Core::Execution::RECURRING,
			Core::Mode::ASYNC,
			Core::Startup::AUTOMATIC,
			1000000000L	//1 FPS
			);
		core.attachSystem(SYS::SYS_SCENE_MANAGER, sceneMngrProcDesc, std::unique_ptr<SceneManager>(new SceneManager()));
	}

	Nle::~Nle()
	{
	}

	bool Nle::initialize()
	{
		assert(!_initialized);
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
		_runningLock->lock();
		_running = true;
		_runningLock->unlock();
		Core::DeviceCore::instance().run();
	}

	void Nle::attachPrintConsole(void(*printConsole)(CONSOLE::OUTPUT_TYPE, const char*))
	{
		assert(!_initialized);
		CONSOLE::Console::instance().attachPrintConsole(printConsole);
	}

	void Nle::stop()
	{
		Core::DeviceCore::instance().stop();
		_runningLock->lock();
		_running = false;
		_runningLock->unlock();
	}

	void Nle::attachPollEvents(void(*pollEvents)(void))
	{
		static_cast<INPUT::IInputProcessor*>(&Core::DeviceCore::instance().getSystemInterface(SYS::SYS_INPUT_PROCESSOR))
			->attachPollEvents(pollEvents);
	}

	void Nle::processEvent(INPUT::Event& event)
	{
		static_cast<INPUT::IInputProcessor*>(&Core::DeviceCore::instance().getSystemInterface(SYS::SYS_INPUT_PROCESSOR))
			->processEvent(event);
	}

	void Nle::setWindowHandle(void* handle)
	{
		static_cast<GRAPHICS::IRenderingEngine*>(&Core::DeviceCore::instance().getSystemInterface(SYS::SYS_RENDERING_ENGINE))
			->setWindowHandle(handle);
	}

	void Nle::executeScript(const char* script)
	{
		bool running;
		_runningLock->lock();
		running = _running;
		_runningLock->unlock();
		static_cast<UI::UiManager*>(&Core::DeviceCore::instance().getSystemInterface(SYS::SYS_UI_MANAGER))
			->executeScript(script, running);
	}

	void Nle::bindScriptCallback(const char* name, int(*callback)(lua_State* state))
	{
		bool running;
		_runningLock->lock();
		running = _running;
		_runningLock->unlock();
		static_cast<UI::UiManager*>(&Core::DeviceCore::instance().getSystemInterface(SYS::SYS_UI_MANAGER))
			->bindScriptCallback(name, callback, running);
	}
}
