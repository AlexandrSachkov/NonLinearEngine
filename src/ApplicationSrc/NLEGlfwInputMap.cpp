/*
-----------------------------------------------------------------------------
This source file is part of NLE
(NonLinear Engine)
For the latest info, see https://github.com/AlexandrSachkov/NonLinearEngine

Copyright (c) 2014 Alexandr Sachkov & NonLinear Engine Team

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/

#include "stdafx.h"

#include "Application\NLEGlfwInputMap.h"
#include "GLFW\glfw3.h"

namespace NLE_INPUT
{
	NLE_INPUT::KEY GLFWtoNLEKey(int key)
	{
		switch (key)
		{
		case GLFW_KEY_UNKNOWN:		return NLE_INPUT::KEY::KEY_UNKNOWN;
		case GLFW_KEY_SPACE:		return NLE_INPUT::KEY::KEY_SPACE;
		case GLFW_KEY_APOSTROPHE:	return NLE_INPUT::KEY::KEY_APOSTROPHE;	/* ' */
		case GLFW_KEY_COMMA:		return NLE_INPUT::KEY::KEY_COMMA;		/* , */
		case GLFW_KEY_MINUS:		return NLE_INPUT::KEY::KEY_MINUS;		/* - */
		case GLFW_KEY_PERIOD:		return NLE_INPUT::KEY::KEY_PERIOD;		/* . */
		case GLFW_KEY_SLASH:		return NLE_INPUT::KEY::KEY_SLASH;		/* / */

		case GLFW_KEY_0:			return NLE_INPUT::KEY::KEY_0;
		case GLFW_KEY_1:			return NLE_INPUT::KEY::KEY_1;
		case GLFW_KEY_2:			return NLE_INPUT::KEY::KEY_2;
		case GLFW_KEY_3:			return NLE_INPUT::KEY::KEY_3;
		case GLFW_KEY_4:			return NLE_INPUT::KEY::KEY_4;
		case GLFW_KEY_5:			return NLE_INPUT::KEY::KEY_5;
		case GLFW_KEY_6:			return NLE_INPUT::KEY::KEY_6;
		case GLFW_KEY_7:			return NLE_INPUT::KEY::KEY_7;
		case GLFW_KEY_8:			return NLE_INPUT::KEY::KEY_8;
		case GLFW_KEY_9:			return NLE_INPUT::KEY::KEY_9;

		case GLFW_KEY_SEMICOLON:	return NLE_INPUT::KEY::KEY_SEMICOLON;	/* ; */
		case GLFW_KEY_EQUAL:		return NLE_INPUT::KEY::KEY_EQUAL;		/* = */

		case GLFW_KEY_A:			return NLE_INPUT::KEY::KEY_A;
		case GLFW_KEY_B:			return NLE_INPUT::KEY::KEY_B;
		case GLFW_KEY_C:			return NLE_INPUT::KEY::KEY_C;
		case GLFW_KEY_D:			return NLE_INPUT::KEY::KEY_D;
		case GLFW_KEY_E:			return NLE_INPUT::KEY::KEY_E;
		case GLFW_KEY_F:			return NLE_INPUT::KEY::KEY_F;
		case GLFW_KEY_G:			return NLE_INPUT::KEY::KEY_G;
		case GLFW_KEY_H:			return NLE_INPUT::KEY::KEY_H;
		case GLFW_KEY_I:			return NLE_INPUT::KEY::KEY_I;
		case GLFW_KEY_J:			return NLE_INPUT::KEY::KEY_J;
		case GLFW_KEY_K:			return NLE_INPUT::KEY::KEY_K;
		case GLFW_KEY_L:			return NLE_INPUT::KEY::KEY_L;
		case GLFW_KEY_M:			return NLE_INPUT::KEY::KEY_M;
		case GLFW_KEY_N:			return NLE_INPUT::KEY::KEY_N;
		case GLFW_KEY_O:			return NLE_INPUT::KEY::KEY_O;
		case GLFW_KEY_P:			return NLE_INPUT::KEY::KEY_P;
		case GLFW_KEY_Q:			return NLE_INPUT::KEY::KEY_Q;
		case GLFW_KEY_R:			return NLE_INPUT::KEY::KEY_R;
		case GLFW_KEY_S:			return NLE_INPUT::KEY::KEY_S;
		case GLFW_KEY_T:			return NLE_INPUT::KEY::KEY_T;
		case GLFW_KEY_U:			return NLE_INPUT::KEY::KEY_U;
		case GLFW_KEY_V:			return NLE_INPUT::KEY::KEY_V;
		case GLFW_KEY_W:			return NLE_INPUT::KEY::KEY_W;
		case GLFW_KEY_X:			return NLE_INPUT::KEY::KEY_X;
		case GLFW_KEY_Y:			return NLE_INPUT::KEY::KEY_Y;
		case GLFW_KEY_Z:			return NLE_INPUT::KEY::KEY_Z;

		case GLFW_KEY_LEFT_BRACKET:			return NLE_INPUT::KEY::KEY_LEFT_BRACKET;		/* [ */
		case GLFW_KEY_BACKSLASH:			return NLE_INPUT::KEY::KEY_BACKSLASH;			/* \ */
		case GLFW_KEY_RIGHT_BRACKET:		return NLE_INPUT::KEY::KEY_RIGHT_BRACKET;		/* ] */
		case GLFW_KEY_GRAVE_ACCENT:			return NLE_INPUT::KEY::KEY_GRAVE_ACCENT;		/* ` */
		case GLFW_KEY_WORLD_1:				return NLE_INPUT::KEY::KEY_WORLD_1;				/* non-US #1 */
		case GLFW_KEY_WORLD_2:				return NLE_INPUT::KEY::KEY_WORLD_2;				/* non-US #2 */
		case GLFW_KEY_ESCAPE:				return NLE_INPUT::KEY::KEY_ESCAPE;
		case GLFW_KEY_ENTER:				return NLE_INPUT::KEY::KEY_ENTER;
		case GLFW_KEY_TAB:					return NLE_INPUT::KEY::KEY_TAB;
		case GLFW_KEY_BACKSPACE:			return NLE_INPUT::KEY::KEY_BACKSPACE;
		case GLFW_KEY_INSERT:				return NLE_INPUT::KEY::KEY_INSERT;
		case GLFW_KEY_DELETE:				return NLE_INPUT::KEY::KEY_DELETE;
		case GLFW_KEY_RIGHT:				return NLE_INPUT::KEY::KEY_RIGHT;
		case GLFW_KEY_LEFT:					return NLE_INPUT::KEY::KEY_LEFT;
		case GLFW_KEY_DOWN:					return NLE_INPUT::KEY::KEY_DOWN;
		case GLFW_KEY_UP:					return NLE_INPUT::KEY::KEY_UP;
		case GLFW_KEY_PAGE_UP:				return NLE_INPUT::KEY::KEY_PAGE_UP;
		case GLFW_KEY_PAGE_DOWN:			return NLE_INPUT::KEY::KEY_PAGE_DOWN;
		case GLFW_KEY_HOME:					return NLE_INPUT::KEY::KEY_HOME;
		case GLFW_KEY_END:					return NLE_INPUT::KEY::KEY_END;
		case GLFW_KEY_CAPS_LOCK:			return NLE_INPUT::KEY::KEY_CAPS_LOCK;
		case GLFW_KEY_SCROLL_LOCK:			return NLE_INPUT::KEY::KEY_SCROLL_LOCK;
		case GLFW_KEY_NUM_LOCK:				return NLE_INPUT::KEY::KEY_NUM_LOCK;
		case GLFW_KEY_PRINT_SCREEN:			return NLE_INPUT::KEY::KEY_PRINT_SCREEN;
		case GLFW_KEY_PAUSE:				return NLE_INPUT::KEY::KEY_PAUSE;

		case GLFW_KEY_F1:					return NLE_INPUT::KEY::KEY_F1;
		case GLFW_KEY_F2:					return NLE_INPUT::KEY::KEY_F2;
		case GLFW_KEY_F3:					return NLE_INPUT::KEY::KEY_F3;
		case GLFW_KEY_F4:					return NLE_INPUT::KEY::KEY_F4;
		case GLFW_KEY_F5:					return NLE_INPUT::KEY::KEY_F5;
		case GLFW_KEY_F6:					return NLE_INPUT::KEY::KEY_F6;
		case GLFW_KEY_F7:					return NLE_INPUT::KEY::KEY_F7;
		case GLFW_KEY_F8:					return NLE_INPUT::KEY::KEY_F8;
		case GLFW_KEY_F9:					return NLE_INPUT::KEY::KEY_F9;
		case GLFW_KEY_F10:					return NLE_INPUT::KEY::KEY_F10;
		case GLFW_KEY_F11:					return NLE_INPUT::KEY::KEY_F11;
		case GLFW_KEY_F12:					return NLE_INPUT::KEY::KEY_F12;
		case GLFW_KEY_F13:					return NLE_INPUT::KEY::KEY_F13;
		case GLFW_KEY_F14:					return NLE_INPUT::KEY::KEY_F14;
		case GLFW_KEY_F15:					return NLE_INPUT::KEY::KEY_F15;
		case GLFW_KEY_F16:					return NLE_INPUT::KEY::KEY_F16;
		case GLFW_KEY_F17:					return NLE_INPUT::KEY::KEY_F17;
		case GLFW_KEY_F18:					return NLE_INPUT::KEY::KEY_F18;
		case GLFW_KEY_F19:					return NLE_INPUT::KEY::KEY_F19;
		case GLFW_KEY_F20:					return NLE_INPUT::KEY::KEY_F20;
		case GLFW_KEY_F21:					return NLE_INPUT::KEY::KEY_F21;
		case GLFW_KEY_F22:					return NLE_INPUT::KEY::KEY_F22;
		case GLFW_KEY_F23:					return NLE_INPUT::KEY::KEY_F23;
		case GLFW_KEY_F24:					return NLE_INPUT::KEY::KEY_F24;
		case GLFW_KEY_F25:					return NLE_INPUT::KEY::KEY_F25;

		case GLFW_KEY_KP_0:					return NLE_INPUT::KEY::KEY_KP_0;
		case GLFW_KEY_KP_1:					return NLE_INPUT::KEY::KEY_KP_1;
		case GLFW_KEY_KP_2:					return NLE_INPUT::KEY::KEY_KP_2;
		case GLFW_KEY_KP_3:					return NLE_INPUT::KEY::KEY_KP_3;
		case GLFW_KEY_KP_4:					return NLE_INPUT::KEY::KEY_KP_4;
		case GLFW_KEY_KP_5:					return NLE_INPUT::KEY::KEY_KP_5;
		case GLFW_KEY_KP_6:					return NLE_INPUT::KEY::KEY_KP_6;
		case GLFW_KEY_KP_7:					return NLE_INPUT::KEY::KEY_KP_7;
		case GLFW_KEY_KP_8:					return NLE_INPUT::KEY::KEY_KP_8;
		case GLFW_KEY_KP_9:					return NLE_INPUT::KEY::KEY_KP_9;

		case GLFW_KEY_KP_DECIMAL:			return NLE_INPUT::KEY::KEY_KP_DECIMAL;
		case GLFW_KEY_KP_DIVIDE:			return NLE_INPUT::KEY::KEY_KP_DIVIDE;
		case GLFW_KEY_KP_MULTIPLY:			return NLE_INPUT::KEY::KEY_KP_MULTIPLY;
		case GLFW_KEY_KP_SUBTRACT:			return NLE_INPUT::KEY::KEY_KP_SUBTRACT;
		case GLFW_KEY_KP_ADD:				return NLE_INPUT::KEY::KEY_KP_ADD;
		case GLFW_KEY_KP_ENTER:				return NLE_INPUT::KEY::KEY_KP_ENTER;
		case GLFW_KEY_KP_EQUAL:				return NLE_INPUT::KEY::KEY_KP_EQUAL;
		case GLFW_KEY_LEFT_SHIFT:			return NLE_INPUT::KEY::KEY_LEFT_SHIFT;
		case GLFW_KEY_LEFT_CONTROL:			return NLE_INPUT::KEY::KEY_LEFT_CONTROL;
		case GLFW_KEY_LEFT_ALT:				return NLE_INPUT::KEY::KEY_LEFT_ALT;
		case GLFW_KEY_LEFT_SUPER:			return NLE_INPUT::KEY::KEY_LEFT_SUPER;
		case GLFW_KEY_RIGHT_SHIFT:			return NLE_INPUT::KEY::KEY_RIGHT_SHIFT;
		case GLFW_KEY_RIGHT_CONTROL:		return NLE_INPUT::KEY::KEY_RIGHT_CONTROL;
		case GLFW_KEY_RIGHT_ALT:			return NLE_INPUT::KEY::KEY_RIGHT_ALT;
		case GLFW_KEY_RIGHT_SUPER:			return NLE_INPUT::KEY::KEY_RIGHT_SUPER;
		case GLFW_KEY_MENU:					return NLE_INPUT::KEY::KEY_MENU;

		default:							return NLE_INPUT::KEY::KEY_UNKNOWN;
		}
	}

	NLE_INPUT::MOUSE	GLFWtoNLEMouse(int button)
	{
		switch (button)
		{
		case GLFW_MOUSE_BUTTON_LEFT:	return NLE_INPUT::MOUSE::MOUSE_BUTTON_LEFT;
		case GLFW_MOUSE_BUTTON_RIGHT:	return NLE_INPUT::MOUSE::MOUSE_BUTTON_RIGHT;
		case GLFW_MOUSE_BUTTON_MIDDLE:	return NLE_INPUT::MOUSE::MOUSE_BUTTON_MIDDLE;
		case GLFW_MOUSE_BUTTON_4:		return NLE_INPUT::MOUSE::MOUSE_BUTTON_4;
		case GLFW_MOUSE_BUTTON_5:		return NLE_INPUT::MOUSE::MOUSE_BUTTON_5;
		case GLFW_MOUSE_BUTTON_6:		return NLE_INPUT::MOUSE::MOUSE_BUTTON_6;
		case GLFW_MOUSE_BUTTON_7:		return NLE_INPUT::MOUSE::MOUSE_BUTTON_7;
		case GLFW_MOUSE_BUTTON_8:		return NLE_INPUT::MOUSE::MOUSE_BUTTON_8;

		default:						return NLE_INPUT::MOUSE::MOUSE_BUTTON_UNKNOWN;
		}
	}

	NLE_INPUT::MOD	GLFWtoNLEMod(int mod)
	{
		switch (mod)
		{
		case GLFW_MOD_ALT:		return NLE_INPUT::MOD::KEY_MOD_ALT;
		case GLFW_MOD_CONTROL:	return NLE_INPUT::MOD::KEY_MOD_CONTROL;
		case GLFW_MOD_SHIFT:	return NLE_INPUT::MOD::KEY_MOD_SHIFT;
		case GLFW_MOD_SUPER:	return NLE_INPUT::MOD::MOD_SUPER;

		default:				return NLE_INPUT::MOD::KEY_MOD_UNKNOWN;
		}
	}

	NLE_INPUT::ACTION GLFWtoNLEAction(int action)
	{
		switch (action)
		{
		case GLFW_PRESS:	return NLE_INPUT::ACTION::ACTION_PRESS;
		case GLFW_RELEASE:	return NLE_INPUT::ACTION::ACTION_RELEASE;
		case GLFW_REPEAT:	return NLE_INPUT::ACTION::ACTION_REPEAT;

		default:			return NLE_INPUT::ACTION::ACTION_UNKNOWN;
		}
	}
};