#include "NL_Renderer.h"
#include "NLCore\NL_ISystem.h"
#include "NLCore\NL_IEngine.h"
#include "NL_RenderingEngine.h"
#include "NLCore\NL_SDistributor.h"
#include "NL_SharedContainers.h"
#include "NL_Systems.h"
#include "NL_Allocator.h"
#include "NL_Camera.h"

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
			_scene = std::make_unique<Scene>();
			_camera = nullptr;

			_viewProjection = alloc<DirectX::XMMATRIX>(16);
			*_viewProjection = DirectX::XMMatrixIdentity();

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
				std::this_thread::sleep_for(std::chrono::seconds(10));
				return false;
			}

			_procedure = [&](){
				if (!_running)
				{
					printf("Starting Rendering task\n");
					_running.fetch_and_store(true);
					_renderingThread = new std::thread([&](
						Renderer& renderer, 
						std::unique_ptr<RenderingEngine> const& renderingEngine,
						std::unique_ptr<Scene> const& scene
					){
						printf("Rendering Thread running\n");			
						while (renderer.isRunning())
						{
							renderingEngine->render(scene, renderer.getViewProjection());
						}
					}, std::ref(*this), std::ref(_renderingEngine), std::ref(_scene));
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
		}

		void Renderer::release()
		{
			stop();
			_renderingThread->join();
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

		void Renderer::addStaticRenderable(RESOURCES::Renderable& renderable)
		{
			_scene->addStaticRenderable(renderable);
		}

		void Renderer::addLight(RESOURCES::Light& light)
		{
			_scene->addLight(light);
		}
	}
}