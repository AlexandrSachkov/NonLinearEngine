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
#include "NL_WindowManager.h"

#include "lua.hpp"

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
		_defaultGrainSize(6500)
	{
		_running.store(false);

		Core::DeviceCore& core = Core::DeviceCore::instance();

		// Install shared containers
		core.installSContainer<char>(CAMERA_COMMANDS, GRAPHICS::COMMANDS::CAMERA::NUM_COMMANDS, _defaultGrainSize); //one slot for each command
		core.installSContainer<double>(CURSOR_COORDINATES, 2, _defaultGrainSize);	// 2 slots for x and y components
		core.installSContainer<double>(SCROLL_OFFSET, 2, _defaultGrainSize);	// 2 slots for x and y components
		core.installSContainer<DirectX::XMFLOAT4X4>(VIEW_PROJECTION_MATRIX, 1, _defaultGrainSize);
		core.installSContainer<DirectX::XMFLOAT4>(EYE_VECTOR, 1, _defaultGrainSize);
		core.installSContainer<double>(FPS, 1, _defaultGrainSize);
		core.installSContainer<DirectX::XMFLOAT4>(CANVAS_BG_COLOR, 1, _defaultGrainSize);

		// Attach systems
		Core::ExecutionDesc windowProcDesc(
			Core::Priority::STANDARD,
			Core::Execution::RECURRING,
			Core::Mode::SYNC,
			Core::Startup::AUTOMATIC,
			Core::Method::TASK,
			16666666L	//60 FPS,
			);
		core.attachSystem(SYS::SYS_WINDOW_MANAGER, windowProcDesc, std::unique_ptr<WINDOW::WindowManager>(new WINDOW::WindowManager()));

		Core::ExecutionDesc uiManagerProcDesc(
			Core::Priority::LOW,
			Core::Execution::RECURRING,
			Core::Mode::SYNC,
			Core::Startup::AUTOMATIC,
			Core::Method::TASK,
			33333333L	//30 FPS
			);
		core.attachSystem(SYS::SYS_UI_MANAGER, uiManagerProcDesc, std::unique_ptr<UI::UiManager>(new UI::UiManager()));

		Core::ExecutionDesc inputProcDesc(
			Core::Priority::STANDARD,
			Core::Execution::RECURRING,
			Core::Mode::ASYNC,
			Core::Startup::AUTOMATIC,
			Core::Method::TASK,
			16666666L	//60 FPS
			);
		core.attachSystem(SYS::SYS_INPUT_PROCESSOR, inputProcDesc, std::unique_ptr<INPUT::InputProcessor>(new INPUT::InputProcessor()));

		Core::ExecutionDesc cameraMngrProcDesc(
			Core::Priority::STANDARD,
			Core::Execution::RECURRING,
			Core::Mode::ASYNC,
			Core::Startup::AUTOMATIC,
			Core::Method::TASK,
			16666666L	//60 FPS
			);
		core.attachSystem(SYS::SYS_CAMERA_MANAGER, cameraMngrProcDesc, std::unique_ptr<GRAPHICS::CameraManager>(new GRAPHICS::CameraManager()));

		Core::ExecutionDesc renderingEngineProcDesc(
			Core::Priority::STANDARD,
			Core::Execution::SINGULAR,
			Core::Mode::ASYNC,
			Core::Startup::AUTOMATIC,
			Core::Method::THREAD,
			0L
			//16393443L
			//1666666L	//60 FPS		
			);
		core.attachSystem(SYS::SYS_RENDERING_ENGINE, renderingEngineProcDesc, std::unique_ptr<GRAPHICS::RenderingEngine>(new GRAPHICS::RenderingEngine()));

		Core::ExecutionDesc sceneMngrProcDesc(
			Core::Priority::STANDARD,
			Core::Execution::RECURRING,
			Core::Mode::ASYNC,
			Core::Startup::AUTOMATIC,
			Core::Method::TASK,
			1000000000L	//1 FPS
			);
		core.attachSystem(SYS::SYS_SCENE_MANAGER, sceneMngrProcDesc, std::unique_ptr<SceneManager>(new SceneManager()));
	}

	Nle::~Nle()
	{
	}

	bool Nle::initialize(Size2D screenSize, bool fullscreen, bool decorated, std::wstring title)
	{
		assert(!_initialized);

		static_cast<GRAPHICS::ICameraManager*>(&Core::DeviceCore::instance().getSystemInterface(SYS::SYS_CAMERA_MANAGER))
			->setScreenDimensions(screenSize.width, screenSize.height);

		std::unique_ptr<WINDOW::Initializer> windowInit = std::make_unique<WINDOW::Initializer>();
		windowInit->screenSize = screenSize;
		windowInit->fullscreen = fullscreen;
		windowInit->decorated = decorated;
		windowInit->title = title;
		windowInit->openglMajorVersion = 4;
		windowInit->openglMinorVersion = 5;
		Core::DeviceCore::instance().setSystemInitializer(SYS::SYS_WINDOW_MANAGER, std::move(windowInit));

		std::unique_ptr<GRAPHICS::CameraManagerInitializer> camInit = std::make_unique<GRAPHICS::CameraManagerInitializer>();
		camInit->screenSize = screenSize;
		Core::DeviceCore::instance().setSystemInitializer(SYS::SYS_CAMERA_MANAGER, std::move(camInit));

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

