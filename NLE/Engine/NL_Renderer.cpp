#include "NL_Renderer.h"
#include "NLCore\NL_ISystem.h"
#include "NLCore\NL_IEngine.h"
#include "NL_RenderingEngine.h"
#include "NLCore\NL_SDistributor.h"
#include "NL_SharedContainers.h"
#include "NL_Systems.h"
#include "NL_Allocator.h"
#include "NL_Camera.h"
#include "NL_ISceneManager.h"
#include "NL_Systems.h"
#include "NLCore\NL_DeviceCore.h"
#include "NL_Console.h"

#include <assert.h>
#include <iostream>  
#include <thread>     
#include <chrono>

#define _USE_MATH_DEFINES
#include <math.h>

namespace NLE
{
	namespace GRAPHICS
	{
		Renderer::Renderer() :
			_initialized(false),
			_firstMouse(true),
			_screenWidth(0),
			_screenHeight(0)
		{
			_running.fetch_and_store(false);
			_renderingEngine = std::make_unique<RenderingEngine>();
			_camera = nullptr;

			_viewProjection = alloc<DirectX::XMMATRIX>(16);
			*_viewProjection = DirectX::XMMatrixIdentity();
			_eye = NLE::alloc<DirectX::XMVECTOR>(16);
			*_eye = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

			_lastCursorX = 0.0f;
			_lastCursorY = 0.0f;
			_firstCameraUpdate = true;
		}

		Renderer::~Renderer()
		{

		}

		bool Renderer::initialize(Core::IEngine& engine)
		{
			assert(!_initialized && _screenWidth > 0 && _screenHeight > 0);

			_camera = std::make_unique<Camera>(0.0f, 0.5f, -10.0f, _screenWidth, _screenHeight);

			_cameraCommands = &static_cast<NLE::Core::Data::SDistributor<char>*>(&engine.getSDistributor(CAMERA_COMMANDS))->buildEndpoint(SYS::SYS_RENDERER);
			_cursorCoords = &static_cast<NLE::Core::Data::SDistributor<double>*>(&engine.getSDistributor(CURSOR_COORDINATES))->buildEndpoint(SYS::SYS_RENDERER);
			_scrollOffset = &static_cast<NLE::Core::Data::SDistributor<double>*>(&engine.getSDistributor(SCROLL_OFFSET))->buildEndpoint(SYS::SYS_RENDERER);

			if (!_renderingEngine->initialize())
			{
				return false;
			}

			_renderingThread.setProcedure([&]() {
				Scene* scene = static_cast<ISceneManager*>(&Core::DeviceCore::instance().getSystemInterface(SYS::SYS_SCENE_MANAGER))
					->getGScene();
				_renderingEngine->render(scene, getViewProjection(), getEye());
			});

			_running.fetch_and_store(true);
			_procedure = [&](){
				if (_running && !_renderingThread.isRunning())
				{
					CONSOLE::out(CONSOLE::STANDARD, L"Starting Rendering thread");
					_renderingThread.start();
				}
				computeViewProjection();
			};

			_initialized = true;
			return true;
		}

		void Renderer::computeViewProjection()
		{
			auto cameraCommands = *_cameraCommands;
			auto cursorCoords = *_cursorCoords;
			auto scrollOffset = *_scrollOffset;

			if (cameraCommands[COMMANDS::CAMERA::FORWARD] && !cameraCommands[COMMANDS::CAMERA::REVERSE])
			{
				_camera->moveForward();
			}
			else if (cameraCommands[COMMANDS::CAMERA::REVERSE] && !cameraCommands[COMMANDS::CAMERA::FORWARD])
			{
				_camera->moveBackward();
			}

			if (cameraCommands[COMMANDS::CAMERA::LEFT] && !cameraCommands[COMMANDS::CAMERA::RIGHT])
			{
				_camera->moveLeft();
			}
			else if (cameraCommands[COMMANDS::CAMERA::RIGHT] && !cameraCommands[COMMANDS::CAMERA::LEFT])
			{
				_camera->moveRight();
			}

			float xPos = (float)cursorCoords[0];	// retrieve cursor x coordinate
			float yPos = (float)cursorCoords[1];	// retrieve cursor y coordinate

			if (_firstCameraUpdate)
			{
				_lastCursorX = xPos;
				_lastCursorY = yPos;
				_firstCameraUpdate = false;
			}

			float yaw = xPos - _lastCursorX;
			float pitch = yPos - _lastCursorY;
			_lastCursorX = xPos;
			_lastCursorY = yPos;

			_camera->rotate(yaw * 0.001f, pitch * 0.001f);
			
			_camera->update();
			setViewProjection(_camera->getViewProjection());
			setEye(_camera->getEye());
		}

		void Renderer::setViewProjection(DirectX::XMMATRIX& viewProjection)
		{
			tbb::spin_mutex::scoped_lock lock(_viewProjectionLock);
			*_viewProjection = viewProjection;
		}

		DirectX::XMMATRIX Renderer::getViewProjection()
		{
			tbb::spin_mutex::scoped_lock lock(_viewProjectionLock);
			return *_viewProjection;
		}

		void Renderer::setEye(DirectX::XMVECTOR& eye)
		{
			tbb::spin_mutex::scoped_lock lock(_eyeLock);
			*_eye = eye;
		}

		DirectX::XMVECTOR Renderer::getEye()
		{
			tbb::spin_mutex::scoped_lock lock(_eyeLock);
			return *_eye;
		}

		float Renderer::toRadians(float degrees)
		{
			const double halfC = M_PI / 180;
			return (float)((double)degrees * halfC);
		}

		bool Renderer::isRunning()
		{
			return _running;
		}
		
		void Renderer::stop()
		{
			_running.fetch_and_store(false);
			_renderingThread.stopAndJoin();
		}

		void Renderer::release()
		{
			_renderingEngine->release();
			_initialized = false;
		}

		bool Renderer::initialized()
		{
			return _initialized;
		}

		std::function<void()> const& Renderer::getExecutionProcedure()
		{
			return _procedure;
		}

		Core::ISystem& Renderer::getInterface()
		{
			return *this;
		}

		void Renderer::setWindowHandle(void* handle)
		{
			_renderingEngine->setWindowHandle(handle);
		}

		void Renderer::setScreenDimensions(uint_fast32_t width, uint_fast32_t height)
		{
			_screenWidth = width;
			_screenHeight = height;

			_renderingEngine->setScreenDimensions(width, height);
		}

		void Renderer::setFullscreen(bool fullscreen)
		{
			_renderingEngine->setFullscreen(fullscreen);
		}

		ID3D11Device* Renderer::getDevice()
		{
			return _renderingEngine->getDevice();
		}
	}
}