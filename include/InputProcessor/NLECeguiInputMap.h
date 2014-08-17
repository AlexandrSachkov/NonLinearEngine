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

#ifndef NLE_CEGUI_INPUT_MAP_
#define NLE_CEGUI_INPUT_MAP_

#include "CEGUI\CEGUI.h"
#include "InputProcessor\NLEInputMap.h"

namespace NLE_INPUT
{
	static unsigned int NLEtoCEGUIKey(NLE_INPUT::KEY key)
	{
		switch (key)
		{
		case NLE_INPUT::KEY_UNKNOWN:	return 0;
		case NLE_INPUT::KEY_ESCAPE:		return CEGUI::Key::Escape;

		case NLE_INPUT::KEY_0:			return CEGUI::Key::Zero;
		case NLE_INPUT::KEY_1:			return CEGUI::Key::One;
		case NLE_INPUT::KEY_2:			return CEGUI::Key::Two;
		case NLE_INPUT::KEY_3:			return CEGUI::Key::Three;
		case NLE_INPUT::KEY_4:			return CEGUI::Key::Four;
		case NLE_INPUT::KEY_5:			return CEGUI::Key::Five;
		case NLE_INPUT::KEY_6:			return CEGUI::Key::Six;
		case NLE_INPUT::KEY_7:			return CEGUI::Key::Seven;
		case NLE_INPUT::KEY_8:			return CEGUI::Key::Eight;
		case NLE_INPUT::KEY_9:			return CEGUI::Key::Nine;

		case NLE_INPUT::KEY_MINUS:		return CEGUI::Key::Minus;
		case NLE_INPUT::KEY_EQUAL:		return CEGUI::Key::Equals;
		case NLE_INPUT::KEY_BACKSPACE:	return CEGUI::Key::Backspace;
		case NLE_INPUT::KEY_TAB:		return CEGUI::Key::Tab;

		case NLE_INPUT::KEY_A:			return CEGUI::Key::A;
		case NLE_INPUT::KEY_B:			return CEGUI::Key::B;
		case NLE_INPUT::KEY_C:			return CEGUI::Key::C;
		case NLE_INPUT::KEY_D:			return CEGUI::Key::D;
		case NLE_INPUT::KEY_E:			return CEGUI::Key::E;
		case NLE_INPUT::KEY_F:			return CEGUI::Key::F;
		case NLE_INPUT::KEY_G:			return CEGUI::Key::G;
		case NLE_INPUT::KEY_H:			return CEGUI::Key::H;
		case NLE_INPUT::KEY_I:			return CEGUI::Key::I;
		case NLE_INPUT::KEY_J:			return CEGUI::Key::J;
		case NLE_INPUT::KEY_K:			return CEGUI::Key::K;
		case NLE_INPUT::KEY_L:			return CEGUI::Key::L;
		case NLE_INPUT::KEY_M:			return CEGUI::Key::M;
		case NLE_INPUT::KEY_N:			return CEGUI::Key::N;
		case NLE_INPUT::KEY_O:			return CEGUI::Key::O;
		case NLE_INPUT::KEY_P:			return CEGUI::Key::P;
		case NLE_INPUT::KEY_Q:			return CEGUI::Key::Q;
		case NLE_INPUT::KEY_R:			return CEGUI::Key::R;
		case NLE_INPUT::KEY_S:			return CEGUI::Key::S;
		case NLE_INPUT::KEY_T:			return CEGUI::Key::T;
		case NLE_INPUT::KEY_U:			return CEGUI::Key::U;
		case NLE_INPUT::KEY_V:			return CEGUI::Key::V;
		case NLE_INPUT::KEY_W:			return CEGUI::Key::W;
		case NLE_INPUT::KEY_X:			return CEGUI::Key::X;
		case NLE_INPUT::KEY_Y:			return CEGUI::Key::Y;
		case NLE_INPUT::KEY_Z:			return CEGUI::Key::Z;

		case NLE_INPUT::KEY_SEMICOLON:		return CEGUI::Key::Semicolon;
		case NLE_INPUT::KEY_APOSTROPHE:		return CEGUI::Key::Apostrophe;
		case NLE_INPUT::KEY_GRAVE_ACCENT:	return CEGUI::Key::Grave;
		case NLE_INPUT::KEY_LEFT_SHIFT:		return CEGUI::Key::LeftShift;
		case NLE_INPUT::KEY_RIGHT_SHIFT:	return CEGUI::Key::RightShift;
		case NLE_INPUT::KEY_BACKSLASH:		return CEGUI::Key::Backslash;
		case NLE_INPUT::KEY_COMMA:			return CEGUI::Key::Comma;
		case NLE_INPUT::KEY_PERIOD:			return CEGUI::Key::Period;
		case NLE_INPUT::KEY_SLASH:			return CEGUI::Key::Slash;
		case NLE_INPUT::KEY_KP_MULTIPLY:	return CEGUI::Key::Multiply;
		case NLE_INPUT::KEY_LEFT_ALT:		return CEGUI::Key::LeftAlt;
		case NLE_INPUT::KEY_RIGHT_ALT:		return CEGUI::Key::RightAlt;
		case NLE_INPUT::KEY_SPACE:			return CEGUI::Key::Space;
		case NLE_INPUT::KEY_CAPS_LOCK:		return CEGUI::Key::Capital;

		case NLE_INPUT::KEY_F1:			return CEGUI::Key::F1;
		case NLE_INPUT::KEY_F2:			return CEGUI::Key::F2;
		case NLE_INPUT::KEY_F3:			return CEGUI::Key::F3;
		case NLE_INPUT::KEY_F4:			return CEGUI::Key::F4;
		case NLE_INPUT::KEY_F5:			return CEGUI::Key::F5;
		case NLE_INPUT::KEY_F6:			return CEGUI::Key::F6;
		case NLE_INPUT::KEY_F7:			return CEGUI::Key::F7;
		case NLE_INPUT::KEY_F8:			return CEGUI::Key::F8;
		case NLE_INPUT::KEY_F9:			return CEGUI::Key::F9;
		case NLE_INPUT::KEY_F10:		return CEGUI::Key::F10;
		case NLE_INPUT::KEY_F11:		return CEGUI::Key::F11;
		case NLE_INPUT::KEY_F12:		return CEGUI::Key::F12;
		case NLE_INPUT::KEY_F13:		return CEGUI::Key::F13;
		case NLE_INPUT::KEY_F14:		return CEGUI::Key::F14;
		case NLE_INPUT::KEY_F15:		return CEGUI::Key::F15;

		case NLE_INPUT::KEY_NUM_LOCK:		return CEGUI::Key::NumLock;
		case NLE_INPUT::KEY_SCROLL_LOCK:	return CEGUI::Key::ScrollLock;

		case NLE_INPUT::KEY_KP_0:			return CEGUI::Key::Numpad0;
		case NLE_INPUT::KEY_KP_1:			return CEGUI::Key::Numpad1;
		case NLE_INPUT::KEY_KP_2:			return CEGUI::Key::Numpad2;
		case NLE_INPUT::KEY_KP_3:			return CEGUI::Key::Numpad3;
		case NLE_INPUT::KEY_KP_4:			return CEGUI::Key::Numpad4;
		case NLE_INPUT::KEY_KP_5:			return CEGUI::Key::Numpad5;
		case NLE_INPUT::KEY_KP_6:			return CEGUI::Key::Numpad6;
		case NLE_INPUT::KEY_KP_7:			return CEGUI::Key::Numpad7;
		case NLE_INPUT::KEY_KP_8:			return CEGUI::Key::Numpad8;
		case NLE_INPUT::KEY_KP_9:			return CEGUI::Key::Numpad9;

		case NLE_INPUT::KEY_KP_DECIMAL:		return CEGUI::Key::Decimal;
		case NLE_INPUT::KEY_KP_EQUAL:		return CEGUI::Key::NumpadEquals;
		case NLE_INPUT::KEY_KP_ENTER:		return CEGUI::Key::NumpadEnter;
		case NLE_INPUT::KEY_UP:				return CEGUI::Key::ArrowUp;
		case NLE_INPUT::KEY_DOWN:			return CEGUI::Key::ArrowDown;
		case NLE_INPUT::KEY_LEFT:			return CEGUI::Key::ArrowLeft;
		case NLE_INPUT::KEY_RIGHT:			return CEGUI::Key::ArrowRight;
		case NLE_INPUT::KEY_LEFT_CONTROL:	return CEGUI::Key::LeftControl;
		case NLE_INPUT::KEY_RIGHT_CONTROL:	return CEGUI::Key::RightControl;
		case NLE_INPUT::KEY_ENTER:			return CEGUI::Key::Return;
		case NLE_INPUT::KEY_INSERT:			return CEGUI::Key::Insert;
		case NLE_INPUT::KEY_DELETE:			return CEGUI::Key::Delete;
		case NLE_INPUT::KEY_PAGE_UP:		return CEGUI::Key::PageUp;
		case NLE_INPUT::KEY_PAGE_DOWN:		return CEGUI::Key::PageDown;
		case NLE_INPUT::KEY_HOME:			return CEGUI::Key::Home;
		case NLE_INPUT::KEY_END:			return CEGUI::Key::End;

		default: return 0;
		}
	}

	static unsigned int NLEtoCEGUIMouse(NLE_INPUT::MOUSE mouse)
	{
		switch (mouse)
		{
		case NLE_INPUT::MOUSE_BUTTON_LEFT:		return CEGUI::MouseButton::LeftButton;
		case NLE_INPUT::MOUSE_BUTTON_RIGHT:		return CEGUI::MouseButton::RightButton;
		case NLE_INPUT::MOUSE_BUTTON_MIDDLE:	return CEGUI::MouseButton::MiddleButton;
		case NLE_INPUT::MOUSE_BUTTON_4:			return CEGUI::MouseButton::X1Button;
		case NLE_INPUT::MOUSE_BUTTON_5:			return CEGUI::MouseButton::X2Button;
		default:								return CEGUI::MouseButton::NoButton;
		}
	}
};
	
#endif