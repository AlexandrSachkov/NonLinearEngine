#include "NL_RenderingEngine.h"

#include <cstdio>
#include <iostream>

namespace NLE
{
	namespace GRAPHICS
	{
		RenderingEngine::RenderingEngine() :
			_frameCount(0),
			_previousTime(std::chrono::nanoseconds(0L))
		{
			printf("Rendering Engine created\n");
		}

		RenderingEngine::~RenderingEngine()
		{

		}

		bool RenderingEngine::initialize()
		{
			return true;
		}

		bool RenderingEngine::initializeOpenGL()
		{
			glewExperimental = true;
			if (glewInit() != GLEW_OK) {
				return false;
			}

			GLuint vertex_shader;
			GLuint fragment_shader;

			// Source code for vertex shader
			static const GLchar * vertex_shader_source[] =
			{
				"#version 430 core \n"
				" \n"
				"void main(void) \n"
				"{ \n"
				
				"const vec4 vertices[3] = vec4[3](vec4(0.25, -0.25, 0.5, 1.0),"
				"vec4(-0.25, -0.25, 0.5, 1.0),"
				"vec4(0.25, 0.25, 0.5, 1.0));"
				
				"gl_Position = vertices[gl_VertexID];"
				"} \n"
			};
			// Source code for fragment shader
			static const GLchar * fragment_shader_source[] =
			{
				"#version 430 core \n"
				" \n"
				"out vec4 color; \n"
				" \n"
				"void main(void) \n"
				"{ \n"
				"color = vec4(sin(gl_FragCoord.x * 0.25) * 0.5 + 0.5,"
				"cos(gl_FragCoord.y * 0.25) * 0.5 + 0.5,"
				"sin(gl_FragCoord.x * 0.15) * cos(gl_FragCoord.y * 0.15),"
				"1.0);"
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
			_program = glCreateProgram();
			glAttachShader(_program, vertex_shader);
			glAttachShader(_program, fragment_shader);
			glLinkProgram(_program);

			// Delete the shaders as the program has them now
			glDeleteShader(vertex_shader);
			glDeleteShader(fragment_shader);

			glGenVertexArrays(1, &_vertexArray);
			glBindVertexArray(_vertexArray);

			// Use the program object we created earlier for rendering
			glUseProgram(_program);
			return true;
		}

		void RenderingEngine::release()
		{
			glDeleteVertexArrays(1, &_vertexArray);
			glDeleteProgram(_program);
		}

		void RenderingEngine::render()
		{
			static const GLfloat green[] = { 0.0f, 1.0f, 0.0f, 1.0f };
			glClearBufferfv(GL_COLOR, 0, green);
			
			glPointSize(40.0f);
			
			// Draw one point
			glDrawArrays(GL_TRIANGLES, 0, 3);

			++_frameCount;
			if (_frameCount == 10000)
			{
				auto time = std::chrono::high_resolution_clock::now();
				auto diff = std::chrono::duration_cast<std::chrono::nanoseconds>(time - _previousTime).count();
				double fps = 1 / (diff / _frameCount * 0.000000001);
				std::cout << fps << "\n";
				_previousTime = time;
				

				_frameCount = 0;
			}
		}
	}
}