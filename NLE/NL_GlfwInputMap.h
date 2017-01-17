#pragma once

#include "NL_InputEvents.h"

namespace NLE
{
	namespace INPUT
	{
		KEY		GLFWtoNLEKey(int key);
		MOUSE	GLFWtoNLEMouse(int button);
		MOD		GLFWtoNLEMod(int mod);
		ACTION	GLFWtoNLEAction(int action);
	}	
};
