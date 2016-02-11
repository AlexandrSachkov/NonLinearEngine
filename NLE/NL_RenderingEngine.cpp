#include "NL_RenderingEngine.h"

#include "NL_ISystem.h"
#include "NL_Systems.h"
#include "NL_IGameManager.h"
#include "NL_IInputProcessor.h"
#include "NL_DeviceCore.h"
#include "NL_ThreadLocal.h"
#include "NL_WindowManager.h"

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
			
			_renderingThread = &Core::DeviceCore::instance().allocateThread();
			_windowManager = new WindowManager();

			_vertexArray = 0;
			CONSOLE::out(CONSOLE::STANDARD, L"Rendering Engine created");
		}

		RenderingEngine::~RenderingEngine()
		{
			
		}

		bool RenderingEngine::initialize(std::unique_ptr<Core::SysInitializer> const& initializer)
		{
			assert(!_initialized);
			_init = static_cast<Initializer*>(initializer.get());
			if (!_init)
			{
				CONSOLE::out(CONSOLE::ERR, "Rendering Engine requires an initializer");
				return false;
			}


			_procedure = [&]() {};

			_renderingThread->setProcedure([&]() {
				if (_firstRun)
				{
					initOpengl();
					_firstRun.store(false);
				}
				_windowManager->pollEvents();
				render();
				_windowManager->swapBuffers();

			}, [&]() {
				releaseOpengl();
			});


			_initialized = true;
			return true;
		}

		void RenderingEngine::initOpengl()
		{
			bool result = _windowManager->initialize(
				_init->screenSize,
				_init->fullscreen,
				_init->decorated,
				L"NonLinear Engine",
				4,
				5
				);
			if (!result)
			{
				CONSOLE::out(CONSOLE::ERR, "WindowManager failed to initialize");
				assert(false);
			}
			_windowManager->makeContextCurrent(true);
			_windowManager->enableVSync(false);
			glewExperimental = TRUE;
			GLenum err = glewInit();
			if (GLEW_OK != err)
			{
				std::string error((const char*)glewGetErrorString(err));
				CONSOLE::out(CONSOLE::ERR, error);
				assert(false);
			}

			_renderProgram = 0;
			GLuint vertex_shader;
			GLuint fragment_shader;
			// Source code for vertex shader
			static const GLchar * vertex_shader_source[] =
			{
				"#version 450 core \n"
				" \n"
				"void main(void) \n"
				"{ \n"
				"	const vec4 vertices[3] = vec4[3](vec4(0.25, -0.25, 0.5, 1.0),\n"
				"	vec4(-0.25, -0.25, 0.5, 1.0),\n"
				"	vec4(0.25, 0.25, 0.5, 1.0));\n"

				"	gl_Position = vertices[gl_VertexID]; \n"
				"} \n"
			};

			static const GLchar * fragment_shader_source[] =
			{
				"#version 450 core \n"
				" \n"
				"out vec4 color; \n"
				" \n"
				"void main(void) \n"
				"{ \n"
				"	color = vec4(sin(gl_FragCoord.x * 0.25) * 0.5 + 0.5,\n"
				"	cos(gl_FragCoord.y * 0.25) * 0.5 + 0.5,"
				"	sin(gl_FragCoord.x * 0.15) * cos(gl_FragCoord.y * 0.15),"
				"	1.0);"
				"} \n"
			};

			// Create and compile vertex shader
			vertex_shader = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vertex_shader, 1, vertex_shader_source, NULL);
			glCompileShader(vertex_shader);
			// Create and compile fragment shader
			fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fragment_shader, 1, fragment_shader_source, NULL);
			glCompileShader(fragment_shader);
			// Create program, attach shaders to it, and link it
			_renderProgram = glCreateProgram();
			glAttachShader(_renderProgram, vertex_shader);
			glAttachShader(_renderProgram, fragment_shader);
			glLinkProgram(_renderProgram);
			// Delete the shaders as the program has them now
			glDeleteShader(vertex_shader);
			glDeleteShader(fragment_shader);

			glCreateVertexArrays(1, &_vertexArray);
			glBindVertexArray(_vertexArray);
		}

		void RenderingEngine::releaseOpengl()
		{
			glDeleteProgram(_renderProgram);
			glDeleteVertexArrays(1, &_vertexArray);
		}

		void RenderingEngine::start()
		{
			_renderingThread->start();
		}

		void RenderingEngine::stop()
		{
			_renderingThread->stop();
		}

		void RenderingEngine::release()
		{
			if (!_initialized)
				return;

			_renderingThread->stopAndJoin();
			if (_windowManager)
				delete _windowManager;
			

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

		void RenderingEngine::render()
		{
			const GLfloat bgColor[] = {0.0f,0.5f,0.6f,1.0f};
			glClearBufferfv(GL_COLOR, 0, bgColor);

			glUseProgram(_renderProgram);
			glDrawArrays(GL_TRIANGLES, 0, 3);

			_timer.sample();
			if (_timer.fpsChanged())
			{
				CONSOLE::out(CONSOLE::STANDARD, std::to_string(_timer.getFps()));
				_timer.reset();
			}
		}

		void RenderingEngine::setWindowTitle(std::wstring title)
		{
			assert(_initialized);
			_windowManager->setTitle(title);
		}
	}
}