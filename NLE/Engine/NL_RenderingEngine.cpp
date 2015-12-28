#include "NL_RenderingEngine.h"

#include "NLCore\NL_ISystem.h"
#include "NLCore\NL_IEngine.h"
#include "NLCore\NL_SDistributor.h"
#include "NL_SharedContainers.h"
#include "NL_Systems.h"
#include "NL_ISceneManager.h"
#include "NL_IInputProcessor.h"
#include "NLCore\NL_DeviceCore.h"
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

			_viewProjection = &static_cast<NLE::Core::Data::SDistributor<DirectX::XMFLOAT4X4>*>(&engine.getSDistributor(VIEW_PROJECTION_MATRIX))->buildEndpoint(SYS::SYS_RENDERING_ENGINE);
			_eye = &static_cast<NLE::Core::Data::SDistributor<DirectX::XMFLOAT4>*>(&engine.getSDistributor(EYE_VECTOR))->buildEndpoint(SYS::SYS_RENDERING_ENGINE);
			_fps = &static_cast<NLE::Core::Data::SDistributor<double>*>(&engine.getSDistributor(FPS))->buildEndpoint(SYS::SYS_RENDERING_ENGINE);
			_canvasBgColor = &static_cast<NLE::Core::Data::SDistributor<DirectX::XMFLOAT4>*>(&engine.getSDistributor(CANVAS_BG_COLOR))->buildEndpoint(SYS::SYS_RENDERING_ENGINE);
			_canvasBgColor->modify(0, DirectX::XMFLOAT4(0.4f, 0.4f, 0.4f, 1.0f));

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

			DirectX::XMMATRIX viewProjection = DirectX::XMLoadFloat4x4(&(*_viewProjection)[0]);
			DirectX::XMVECTOR eye = DirectX::XMLoadFloat4(&(*_eye)[0]);

			const GLfloat bgColor[] = { 
				(*_canvasBgColor)[0].x,
				(*_canvasBgColor)[0].y,
				(*_canvasBgColor)[0].z,
				(*_canvasBgColor)[0].w 
			};
			glClearBufferfv(GL_COLOR, 0, bgColor);

			_timer.sample();
			if (_timer.fpsChanged())
			{
				CONSOLE::out(CONSOLE::STANDARD, std::to_string(_timer.getFps()));
				_fps->modify(0, _timer.getFps());
				_timer.reset();
			}
		}
	}
}