#include "NL_RenderingEngine.h"

#include <cstdio>

namespace NLE
{
	namespace GRAPHICS
	{
		RenderingEngine::RenderingEngine()
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
				" color = vec4(0.0, 0.8, 1.0, 1.0); \n"
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
			// Use the program object we created earlier for rendering
			glUseProgram(_program);
			// Draw one point
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
	}
}