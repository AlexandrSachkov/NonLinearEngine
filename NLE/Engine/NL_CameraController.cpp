#include "NL_CameraController.h"
#include "NLCore\NL_IEngine.h"
#include "NLCore\NL_SDistributor.h"

#include "NL_SharedContainers.h"
#include "NL_Systems.h"

#include <assert.h>

namespace NLE
{
	namespace CAMERA
	{
		CameraController::CameraController() :
			_initialized(false),
			_firstMouse(true),
			_screenWidth(0),
			_screenHeight(0)
		{
			/*_cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
			_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
			_cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);*/
			_cameraSpeedConst = 0.00005f;
			_sensitivity = 0.05f;
			_yaw = 0;
			_pitch = 0;
			_aspect = 1.0f;
		}

		CameraController::~CameraController()
		{

		}

		bool CameraController::initialize(Core::IEngine& engine)
		{
			assert(!_initialized && _screenWidth != 0 && _screenHeight != 0);
			_engine = &engine;

			_commands = &static_cast<NLE::Core::Data::SDistributor<char>*>(&engine.getSDistributor(CAMERA_CONTROLLER_COMMANDS))->buildEndpoint(SYS::SYS_CAMERA_CONTROLLER);
			_cursorCoords = &static_cast<NLE::Core::Data::SDistributor<double>*>(&engine.getSDistributor(CURSOR_COORDINATES))->buildEndpoint(SYS::SYS_CAMERA_CONTROLLER);
			_scrollOffset = &static_cast<NLE::Core::Data::SDistributor<double>*>(&engine.getSDistributor(SCROLL_OFFSET))->buildEndpoint(SYS::SYS_CAMERA_CONTROLLER);
			//_viewProjection = &static_cast<NLE::Core::Data::SDistributor<glm::mat4x4>*>(&engine.getSDistributor(VIEW_PROJECTION))->buildEndpoint(SYS::SYS_CAMERA_CONTROLLER);
		
			_procedure = [&](){
				/*auto commands = *_commands;
				auto cursorCoords = *_cursorCoords;
				auto scrollOffset = *_scrollOffset;
				auto viewProjection = *_viewProjection;

				auto time = std::chrono::high_resolution_clock::now();
				auto diff = std::chrono::duration_cast<std::chrono::nanoseconds>(time - _previousTime).count();
				_previousTime = time;

				float cameraSpeed = _cameraSpeedConst * diff;

				if (commands[FORWARD])
					_cameraPos += cameraSpeed * _cameraFront;
					
				if (commands[REVERSE])
					_cameraPos -= cameraSpeed * _cameraFront;
					
				if (commands[LEFT])
					_cameraPos -= glm::normalize(glm::cross(_cameraFront, _cameraUp)) * cameraSpeed;
					
				if (commands[RIGHT])
					_cameraPos += glm::normalize(glm::cross(_cameraFront, _cameraUp)) * cameraSpeed;


				float xpos = (float)cursorCoords[0];	// retrieve cursor x coordinate
				float ypos = (float)cursorCoords[1];	// retrieve cursor y coordinate
				if (_firstMouse)
				{
					_lastX = xpos;
					_lastY = ypos;
					_firstMouse = false;
				}

				float xoffset = xpos - _lastX;
				float yoffset = _lastY - ypos;
				_lastX = xpos;
				_lastY = ypos;

				xoffset *= _sensitivity;
				yoffset *= _sensitivity;

				_yaw += xoffset;
				_pitch += yoffset;

				if (_pitch > 89.0f)
					_pitch = 89.0f;
				if (_pitch < -89.0f)
					_pitch = -89.0f;

				glm::vec3 front;
				front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
				front.y = sin(glm::radians(_pitch));
				front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
				_cameraFront = glm::normalize(front);
					
				float offset = (float)scrollOffset[1];	// retrieve scroll offset on y axis
				if (_aspect >= 1.0f && _aspect <= 45.0f)
					_aspect -= offset;
				if (_aspect <= 1.0f)
					_aspect = 1.0f;
				if (_aspect >= 45.0f)
					_aspect = 45.0f;

				viewProjection.modify(0, glm::lookAt(_cameraPos, _cameraPos + _cameraFront, _cameraUp)); // set view matrix
				viewProjection.modify(1, glm::perspective(_aspect, (float)_screenWidth / (float)_screenHeight, 0.1f, 100.0f)); //set projection matrix*/
			};

			_initialized = true;
			return _initialized;
		}

		void CameraController::release()
		{

		}

		bool CameraController::initialized()
		{
			return _initialized;
		}

		std::function<void()> const& CameraController::getExecutionProcedure()
		{
			return _procedure;
		}

		Core::ISystem& CameraController::getInterface()
		{
			return *this;
		}

		void CameraController::setScreenDimensions(uint_fast32_t width, uint_fast32_t height)
		{
			assert(!_initialized);
			_screenWidth = width;
			_screenHeight = height;
		}
	}
}