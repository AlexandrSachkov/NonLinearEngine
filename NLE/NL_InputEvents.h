#pragma once

namespace NLE
{
	namespace INPUT
	{
		enum KEY
		{
			KEY_UNKNOWN,
			KEY_SPACE,
			KEY_APOSTROPHE,		/* ' */
			KEY_COMMA,			/* , */
			KEY_MINUS,			/* - */
			KEY_PERIOD,			/* . */
			KEY_SLASH,			/* / */

			KEY_0,
			KEY_1,
			KEY_2,
			KEY_3,
			KEY_4,
			KEY_5,
			KEY_6,
			KEY_7,
			KEY_8,
			KEY_9,

			KEY_SEMICOLON,		/* ; */
			KEY_EQUAL,			/* = */

			KEY_A,
			KEY_B,
			KEY_C,
			KEY_D,
			KEY_E,
			KEY_F,
			KEY_G,
			KEY_H,
			KEY_I,
			KEY_J,
			KEY_K,
			KEY_L,
			KEY_M,
			KEY_N,
			KEY_O,
			KEY_P,
			KEY_Q,
			KEY_R,
			KEY_S,
			KEY_T,
			KEY_U,
			KEY_V,
			KEY_W,
			KEY_X,
			KEY_Y,
			KEY_Z,

			KEY_LEFT_BRACKET,		/* [ */
			KEY_BACKSLASH,			/* \ */
			KEY_RIGHT_BRACKET,		/* ] */
			KEY_GRAVE_ACCENT,		/* ` */
			KEY_WORLD_1,			/* non-US #1 */
			KEY_WORLD_2,			/* non-US #2 */
			KEY_ESCAPE,
			KEY_ENTER,
			KEY_TAB,
			KEY_BACKSPACE,
			KEY_INSERT,
			KEY_DELETE,
			KEY_RIGHT,
			KEY_LEFT,
			KEY_DOWN,
			KEY_UP,
			KEY_PAGE_UP,
			KEY_PAGE_DOWN,
			KEY_HOME,
			KEY_END,
			KEY_CAPS_LOCK,
			KEY_SCROLL_LOCK,
			KEY_NUM_LOCK,
			KEY_PRINT_SCREEN,
			KEY_PAUSE,

			KEY_F1,
			KEY_F2,
			KEY_F3,
			KEY_F4,
			KEY_F5,
			KEY_F6,
			KEY_F7,
			KEY_F8,
			KEY_F9,
			KEY_F10,
			KEY_F11,
			KEY_F12,
			KEY_F13,
			KEY_F14,
			KEY_F15,
			KEY_F16,
			KEY_F17,
			KEY_F18,
			KEY_F19,
			KEY_F20,
			KEY_F21,
			KEY_F22,
			KEY_F23,
			KEY_F24,
			KEY_F25,

			KEY_KP_0,
			KEY_KP_1,
			KEY_KP_2,
			KEY_KP_3,
			KEY_KP_4,
			KEY_KP_5,
			KEY_KP_6,
			KEY_KP_7,
			KEY_KP_8,
			KEY_KP_9,

			KEY_KP_DECIMAL,
			KEY_KP_DIVIDE,
			KEY_KP_MULTIPLY,
			KEY_KP_SUBTRACT,
			KEY_KP_ADD,
			KEY_KP_ENTER,
			KEY_KP_EQUAL,
			KEY_LEFT_SHIFT,
			KEY_LEFT_CONTROL,
			KEY_LEFT_ALT,
			KEY_LEFT_SUPER,
			KEY_RIGHT_SHIFT,
			KEY_RIGHT_CONTROL,
			KEY_RIGHT_ALT,
			KEY_RIGHT_SUPER,
			KEY_MENU,

			NUM_KEYS
		};

		enum MOUSE
		{
			MOUSE_BUTTON_UNKNOWN,
			MOUSE_BUTTON_LEFT,
			MOUSE_BUTTON_RIGHT,
			MOUSE_BUTTON_MIDDLE,
			MOUSE_BUTTON_4,
			MOUSE_BUTTON_5,
			MOUSE_BUTTON_6,
			MOUSE_BUTTON_7,
			MOUSE_BUTTON_8,

			NUM_MOUSE_BUTTONS
		};

		enum MOD
		{
			KEY_MOD_UNKNOWN = 0x0000,
			KEY_MOD_ALT = 0x0001,
			KEY_MOD_CONTROL = 0x0002,
			KEY_MOD_SHIFT = 0x0004,
			KEY_MOD_SUPER = 0x0008,

			NUM_KEY_MODS
		};

		enum ACTION
		{
			ACTION_UNKNOWN,
			ACTION_PRESS,
			ACTION_RELEASE,
			ACTION_REPEAT,

			NUM_ACTIONS
		};

		/////////////////////////////////////////////////

		struct KeyEvent
		{
			KEY key;
			int scancode;
			ACTION action;
			MOD mods;
		};

		struct CharEvent
		{
			unsigned int code;
		};

		struct MouseButtonEvent
		{
			MOUSE button;
			ACTION action;
			MOD mods;
		};

		struct CursorPositionEvent
		{
			double xPos;
			double yPos;
		};

		struct CursorEnterEvent
		{
			bool entered;
		};

		struct ScrollEvent
		{
			double xOffset;
			double yOffset;
		};

		//////////////////////////////////////////////////
		struct WindowPositionEvent
		{
			int xPos;
			int yPos;
		};

		struct WindowSizeEvent
		{
			int width;
			int height;
		};

		struct WindowCloseEvent
		{
		};

		struct WindowRefreshEvent
		{
		};

		struct WindowFocusEvent
		{
			bool focused;
		};

		struct WindowIconifyEvent
		{
			bool iconified;
		};


		///////////////////////////////////////////////////
		struct ClipboardCopyEvent
		{
		};

		struct ClipboardCutEvent
		{
		};

		struct ClipboardPasteEvent
		{
		};

		///////////////////////////////////////////////////

		enum EVENT_TYPE
		{
			EVENT_KEY,
			EVENT_CHAR,
			EVENT_MOUSE_BUTTON,
			EVENT_CURSOR_POSITION,
			EVENT_CURSOR_ENTER,
			EVENT_SCROLL,

			EVENT_WINDOW_POSITION,
			EVENT_WINDOW_SIZE,
			EVENT_WINDOW_CLOSE,
			EVENT_WINDOW_REFRESH,
			EVENT_WINDOW_FOCUS,
			EVENT_WINDOW_ICONIFY,

			EVENT_CLIPBOARD_COPY,
			EVENT_CLIPBOARD_CUT,
			EVENT_CLIPBOARD_PASTE
		};

		union EventData
		{
			KeyEvent				keyEvent;
			CharEvent				charEvent;
			MouseButtonEvent		mouseButtonEvent;
			CursorPositionEvent		cursorPositionEvent;
			CursorEnterEvent		cursorEnterEvent;
			ScrollEvent				scrollEvent;

			WindowPositionEvent		windowPositionEvent;
			WindowSizeEvent			windowSizeEvent;
			WindowCloseEvent		windowCloseEvent;
			WindowRefreshEvent		windowRefreshEvent;
			WindowFocusEvent		windowFocusEvent;
			WindowIconifyEvent		windowIconifyEvent;

			ClipboardCopyEvent		clipboardCopyEvent;
			ClipboardCutEvent		clipboardCutEvent;
			ClipboardPasteEvent		clipboardPasteEvent;
		};

		struct Event
		{
			EVENT_TYPE		eventType;
			EventData		eventData;
		};
	}
};