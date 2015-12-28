#include "NL_CameraManager.h"
#include "NLCore\NL_ISystem.h"
#include "NLCore\NL_IEngine.h"
#include "NLCore\NL_SDistributor.h"
#include "NL_SharedContainers.h"
#include "NL_Systems.h"
#include "NL_Allocator.h"
#include "NL_Camera.h"
#include "NL_Systems.h"
#include "NL_Console.h"
#include "NLCore\NL_SysInitializer.h"

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
		CameraManager::CameraManager() :
			_initialized(false),
			_firstMouse(true),
			_screenWidth(0),
			_screenHeight(0)
		{
			_camera = nullptr;

			_lastCursorX = 0.0f;
			_lastCursorY = 0.0f;
			_firstCameraUpdate = true;
		}

		CameraManager::~CameraManager()
		{

		}

		bool CameraManager::initialize(Core::IEngine& engine, std::unique_ptr<Core::SysInitializer> const& initializer)
		{
			assert(!_initialized && _screenWidth > 0 && _screenHeight > 0);

			_camera = std::make_unique<Camera>(0.0f, 0.5f, -10.0f, _screenWidth, _screenHeight);

			_cameraCommands = &static_cast<NLE::Core::Data::SDistributor<char>*>(&engine.getSDistributor(CAMERA_COMMANDS))->buildEndpoint(SYS::SYS_CAMERA_MANAGER);
			_cursorCoords = &static_cast<NLE::Core::Data::SDistributor<double>*>(&engine.getSDistributor(CURSOR_COORDINATES))->buildEndpoint(SYS::SYS_CAMERA_MANAGER);
			_scrollOffset = &static_cast<NLE::Core::Data::SDistributor<double>*>(&engine.getSDistributor(SCROLL_OFFSET))->buildEndpoint(SYS::SYS_CAMERA_MANAGER);
			_viewProjection = &static_cast<NLE::Core::Data::SDistributor<DirectX::XMFLOAT4X4>*>(&engine.getSDistributor(VIEW_PROJECTION_MATRIX))->buildEndpoint(SYS::SYS_CAMERA_MANAGER);
			_eye = &static_cast<NLE::Core::Data::SDistributor<DirectX::XMFLOAT4>*>(&engine.getSDistributor(EYE_VECTOR))->buildEndpoint(SYS::SYS_CAMERA_MANAGER);

			DirectX::XMFLOAT4X4 viewProjection;
			DirectX::XMStoreFloat4x4(&viewProjection, DirectX::XMMatrixIdentity());
			_viewProjection->modify(0, viewProjection);

			DirectX::XMFLOAT4 eye(0.0f, 0.0f, 0.0f, 0.0f);
			_eye->modify(0, eye);

			_procedure = [&](){
				computeViewProjection();
			};

			_initialized = true;
			return true;
		}

		void CameraManager::computeViewProjection()
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
			
			DirectX::XMFLOAT4X4 viewProjection;
			DirectX::XMStoreFloat4x4(&viewProjection, _camera->getViewProjection());
			_viewProjection->modify(0, viewProjection);

			DirectX::XMFLOAT4 eye;
			DirectX::XMStoreFloat4(&eye, _camera->getEye());
			_eye->modify(0, eye);
		}

		float CameraManager::toRadians(float degrees)
		{
			const double halfC = M_PI / 180;
			return (float)((double)degrees * halfC);
		}

		void CameraManager::release()
		{
			_initialized = false;
		}

		bool CameraManager::initialized()
		{
			return _initialized;
		}

		std::function<void()> const& CameraManager::getExecutionProcedure()
		{
			return _procedure;
		}

		Core::ISystem& CameraManager::getInterface()
		{
			return *this;
		}

		void CameraManager::setScreenDimensions(uint_fast32_t width, uint_fast32_t height)
		{
			_screenWidth = width;
			_screenHeight = height;		
		}
	}
}