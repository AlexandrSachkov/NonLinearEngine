#include "NL_RenderingEngine.h"

#include "GL\glew.h"
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

			return true;
		}

		void RenderingEngine::release()
		{

		}

		void RenderingEngine::render()
		{
			glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
		}
	}
}