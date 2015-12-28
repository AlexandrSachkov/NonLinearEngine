#include "NL_RenderingEngine.h"

#include "NL_ISystem.h"
#include "NL_IEngine.h"
#include "NL_Systems.h"
#include "NL_ISceneManager.h"
#include "NL_IInputProcessor.h"
#include "NL_DeviceCore.h"
#include "NL_ThreadLocal.h"
#include "NL_WindowManager.h"

#include "gl\glew.h"

#include "NL_GScene.h"
#include "NL_Console.h"
#include "lua.hpp"


namespace NLE
{
	namespace GRAPHICS
	{
		RenderingEngine::RenderingEngine() :
			_initialized(false),
			_timer(100)
		{
			_firstRun.store(true);
			CONSOLE::out(CONSOLE::STANDARD, L"Rendering Engine created");
		}

		RenderingEngine::~RenderingEngine()
		{
		}

		bool RenderingEngine::initialize(Core::IEngine& engine, std::unique_ptr<Core::SysInitializer> const& initializer)
		{
			assert(!_initialized);

			_windowManager = static_cast<WINDOW::IWindowManager*>(&Core::DeviceCore::instance().getSystemInterface(SYS::SYS_WINDOW_MANAGER));
			
			_procedure = [&]() {
				if (_firstRun)
				{
					_windowManager->makeContextCurrent(true);
					_windowManager->enableVSync(false);
					GLenum err = glewInit();
					if (GLEW_OK != err)
					{
						std::string error((const char*)glewGetErrorString(err));
						CONSOLE::out(CONSOLE::ERR, error);
					}
					_firstRun.store(false);
				}
				render();
				_windowManager->swapBuffers();
			};


			_initialized = true;
			return true;
		}

		void RenderingEngine::start()
		{
			printf("start\n");
		}

		void RenderingEngine::stop()
		{
			printf("stop\n");
		}

		void RenderingEngine::release()
		{
			if (!_initialized)
				return;

			_initialized = false;
		}

		std::function<void()> const& RenderingEngine::getExecutionProcedure()
		{
			return _procedure;
		}

		Core::ISystem& RenderingEngine::getInterface()
		{
			return *this;
		}

		bool RenderingEngine::initialized()
		{
			return _initialized;
		}

		ID3D11Device* RenderingEngine::getDevice()
		{
			assert(_initialized);
			return nullptr;
		}

		void RenderingEngine::render()
		{
			Scene* scene = static_cast<ISceneManager*>(&Core::DeviceCore::instance().getSystemInterface(SYS::SYS_SCENE_MANAGER))
				->getGScene();

			const GLfloat bgColor[] = {0.0f,0.5f,0.6f,1.0f};
			glClearBufferfv(GL_COLOR, 0, bgColor);

			_timer.sample();
			if (_timer.fpsChanged())
			{
				CONSOLE::out(CONSOLE::STANDARD, std::to_string(_timer.getFps()));
				_timer.reset();
			}
		}
	}
}