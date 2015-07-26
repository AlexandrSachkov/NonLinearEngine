#ifndef NL_CAMERA_CONTROLLER_H_
#define NL_CAMERA_CONTROLLER_H_

#include "NLCore\NL_System.h"
#include "NL_ICameraController.h"

#include "NLCore\NL_SContainer.h"

#include <chrono>

namespace NLE
{
	namespace Core
	{
		class IEngine;
	}
	namespace CAMERA
	{
		class CameraController : public Core::System, public ICameraController
		{
		public:
			CameraController(); 
			~CameraController();

			bool initialize(Core::IEngine& engine);
			void release();
			bool initialized();
			std::function<void()> const& getExecutionProcedure();
			Core::ISystem& getInterface();

			void setScreenDimensions(uint_fast32_t width, uint_fast32_t height);
		private:
			bool _initialized;
			Core::IEngine* _engine;
			std::function<void()> _procedure;

			uint_fast32_t _screenWidth;
			uint_fast32_t _screenHeight;

			NLE::Core::Data::SContainer<char>* _commands;
			NLE::Core::Data::SContainer<double>* _cursorCoords;
			NLE::Core::Data::SContainer<double>* _scrollOffset;
			//NLE::Core::Data::SContainer<glm::mat4x4>* _viewProjection;

			std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::nanoseconds> _previousTime;
			float _lastX;
			float _lastY;
			bool _firstMouse;

			/*glm::vec3 _cameraPos;
			glm::vec3 _cameraFront;
			glm::vec3 _cameraUp;*/
			float _cameraSpeedConst;
			float _sensitivity;
			float _yaw;
			float _pitch;
			float _aspect;
		};
	}
}


#endif