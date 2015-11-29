#include "nl_qtinputmap.h"
#include "Windows.h"
namespace NLE
{
    namespace INPUT
    {
    KEY QTtoNLEKey(QKeyEvent* event)
            {
                auto modifiers = event->nativeModifiers();
                switch (event->key())
                {
                //case GLFW_KEY_UNKNOWN:		return KEY_UNKNOWN;
                case Qt::Key_Space:         return KEY_SPACE;
                case Qt::Key_Apostrophe:	return KEY_APOSTROPHE;	/* ' */
                case Qt::Key_Comma:         return KEY_COMMA;		/* , */
                case Qt::Key_Minus:
                    if(modifiers & Qt::KeypadModifier)
                    {
                        return KEY_KP_SUBTRACT;
                    }
                    return KEY_MINUS;		/* - */

                case Qt::Key_Period:
                    if(modifiers & Qt::KeypadModifier)
                    {
                        return KEY_KP_DECIMAL;
                    }
                    return KEY_PERIOD;		/* . */

                case Qt::Key_Slash:         return KEY_SLASH;		/* / */

                case Qt::Key_0:
                    if(modifiers & Qt::KeypadModifier)
                    {
                        return KEY_KP_0;
                    }
                    return KEY_0;

                case Qt::Key_1:
                    if(modifiers & Qt::KeypadModifier)
                    {
                        return KEY_KP_1;
                    }
                    return KEY_1;

                case Qt::Key_2:
                    if(modifiers & Qt::KeypadModifier)
                    {
                        return KEY_KP_2;
                    }
                    return KEY_2;

                case Qt::Key_3:
                    if(modifiers & Qt::KeypadModifier)
                    {
                        return KEY_KP_3;
                    }
                    return KEY_3;

                case Qt::Key_4:
                    if(modifiers & Qt::KeypadModifier)
                    {
                        return KEY_KP_4;
                    }
                    return KEY_4;

                case Qt::Key_5:
                    if(modifiers & Qt::KeypadModifier)
                    {
                        return KEY_KP_5;
                    }
                    return KEY_5;

                case Qt::Key_6:
                    if(modifiers & Qt::KeypadModifier)
                    {
                        return KEY_KP_6;
                    }
                    return KEY_6;

                case Qt::Key_7:
                    if(modifiers & Qt::KeypadModifier)
                    {
                        return KEY_KP_7;
                    }
                    return KEY_7;

                case Qt::Key_8:
                    if(modifiers & Qt::KeypadModifier)
                    {
                        return KEY_KP_8;
                    }
                    return KEY_8;

                case Qt::Key_9:
                    if(modifiers & Qt::KeypadModifier)
                    {
                        return KEY_KP_9;
                    }
                    return KEY_9;

                case Qt::Key_Semicolon:     return KEY_SEMICOLON;	/* ; */

                case Qt::Key_A:			return KEY_A;
                case Qt::Key_B:			return KEY_B;
                case Qt::Key_C:			return KEY_C;
                case Qt::Key_D:			return KEY_D;
                case Qt::Key_E:			return KEY_E;
                case Qt::Key_F:			return KEY_F;
                case Qt::Key_G:			return KEY_G;
                case Qt::Key_H:			return KEY_H;
                case Qt::Key_I:			return KEY_I;
                case Qt::Key_J:			return KEY_J;
                case Qt::Key_K:			return KEY_K;
                case Qt::Key_L:			return KEY_L;
                case Qt::Key_M:			return KEY_M;
                case Qt::Key_N:			return KEY_N;
                case Qt::Key_O:			return KEY_O;
                case Qt::Key_P:			return KEY_P;
                case Qt::Key_Q:			return KEY_Q;
                case Qt::Key_R:			return KEY_R;
                case Qt::Key_S:			return KEY_S;
                case Qt::Key_T:			return KEY_T;
                case Qt::Key_U:			return KEY_U;
                case Qt::Key_V:			return KEY_V;
                case Qt::Key_W:			return KEY_W;
                case Qt::Key_X:			return KEY_X;
                case Qt::Key_Y:			return KEY_Y;
                case Qt::Key_Z:			return KEY_Z;

                case Qt::Key_BracketLeft:			return KEY_LEFT_BRACKET;		/* [ */
                case Qt::Key_Backslash:             return KEY_BACKSLASH;			/* \ */
                case Qt::Key_BracketRight:          return KEY_RIGHT_BRACKET;		/* ] */
                //case Qt::Key_:			return KEY_GRAVE_ACCENT;		/* ` */
                //case GLFW_KEY_WORLD_1:				return KEY_WORLD_1;				/* non-US #1 */
                //case GLFW_KEY_WORLD_2:				return KEY_WORLD_2;				/* non-US #2 */
                case Qt::Key_Escape:				return KEY_ESCAPE;
                case Qt::Key_Enter:
                    if(modifiers & Qt::KeypadModifier)
                    {
                        return KEY_KP_ENTER;
                    }
                    return KEY_ENTER;

                case Qt::Key_Tab:					return KEY_TAB;
                case Qt::Key_Backspace:             return KEY_BACKSPACE;
                case Qt::Key_Insert:				return KEY_INSERT;
                case Qt::Key_Delete:				return KEY_DELETE;
                case Qt::Key_Right:                 return KEY_RIGHT;
                case Qt::Key_Left:					return KEY_LEFT;
                case Qt::Key_Down:					return KEY_DOWN;
                case Qt::Key_Up:					return KEY_UP;
                case Qt::Key_PageUp:				return KEY_PAGE_UP;
                case Qt::Key_PageDown:              return KEY_PAGE_DOWN;
                case Qt::Key_Home:					return KEY_HOME;
                case Qt::Key_End:					return KEY_END;
                case Qt::Key_CapsLock:              return KEY_CAPS_LOCK;
                case Qt::Key_ScrollLock:			return KEY_SCROLL_LOCK;
                case Qt::Key_NumLock:				return KEY_NUM_LOCK;
                case Qt::Key_Print:                 return KEY_PRINT_SCREEN;
                case Qt::Key_Pause:                 return KEY_PAUSE;

                case Qt::Key_F1:					return KEY_F1;
                case Qt::Key_F2:					return KEY_F2;
                case Qt::Key_F3:					return KEY_F3;
                case Qt::Key_F4:					return KEY_F4;
                case Qt::Key_F5:					return KEY_F5;
                case Qt::Key_F6:					return KEY_F6;
                case Qt::Key_F7:					return KEY_F7;
                case Qt::Key_F8:					return KEY_F8;
                case Qt::Key_F9:					return KEY_F9;
                case Qt::Key_F10:					return KEY_F10;
                case Qt::Key_F11:					return KEY_F11;
                case Qt::Key_F12:					return KEY_F12;
                case Qt::Key_F13:					return KEY_F13;
                case Qt::Key_F14:					return KEY_F14;
                case Qt::Key_F15:					return KEY_F15;
                case Qt::Key_F16:					return KEY_F16;
                case Qt::Key_F17:					return KEY_F17;
                case Qt::Key_F18:					return KEY_F18;
                case Qt::Key_F19:					return KEY_F19;
                case Qt::Key_F20:					return KEY_F20;
                case Qt::Key_F21:					return KEY_F21;
                case Qt::Key_F22:					return KEY_F22;
                case Qt::Key_F23:					return KEY_F23;
                case Qt::Key_F24:					return KEY_F24;
                case Qt::Key_F25:					return KEY_F25;

                case Qt::Key_division:              return KEY_KP_DIVIDE;
                case Qt::Key_multiply:              return KEY_KP_MULTIPLY;
                case Qt::Key_Plus:                  return KEY_KP_ADD;
                case Qt::Key_Equal:
                    if(modifiers & Qt::KeypadModifier)
                    {
                        return KEY_KP_EQUAL;
                    }
                    return KEY_EQUAL;		/* = */

                case Qt::Key_Shift:
                    if(event->nativeScanCode()== VK_LSHIFT)
                    {
                        return KEY_LEFT_SHIFT;
                    }
                    return KEY_RIGHT_SHIFT;

                case Qt::Key_Control:
                    if(event->nativeScanCode()== VK_LCONTROL)
                    {
                        return KEY_LEFT_CONTROL;
                    }
                    return KEY_RIGHT_CONTROL;

                case Qt::Key_Alt:
                    if(event->nativeScanCode()== VK_MENU)
                    {
                        return KEY_LEFT_ALT;
                    }
                    return KEY_RIGHT_ALT;

                case Qt::Key_Super_L:               return KEY_LEFT_SUPER;
                case Qt::Key_Super_R:               return KEY_LEFT_SUPER;
                case Qt::Key_Menu:					return KEY_MENU;

                default:							return KEY_UNKNOWN;
                }
            }

            MOUSE	QTtoNLEMouse(QMouseEvent* event)
            {
                switch (event->button())
                {
                case Qt::LeftButton:	return MOUSE_BUTTON_LEFT;
                case Qt::RightButton:	return MOUSE_BUTTON_RIGHT;
                case Qt::MiddleButton:	return MOUSE_BUTTON_MIDDLE;
                case Qt::XButton1:		return MOUSE_BUTTON_4;
                case Qt::XButton2:		return MOUSE_BUTTON_5;
                //case GLFW_MOUSE_BUTTON_6:		return MOUSE_BUTTON_6;
                //case GLFW_MOUSE_BUTTON_7:		return MOUSE_BUTTON_7;
                //case GLFW_MOUSE_BUTTON_8:		return MOUSE_BUTTON_8;

                default:						return MOUSE_BUTTON_UNKNOWN;
                }
            }

            MOD	QTtoNLEMod(QKeyEvent* event)
            {
                auto modifiers = event->nativeModifiers();
                if (modifiers & Qt::ShiftModifier)
                    return KEY_MOD_SHIFT;
                if (modifiers & Qt::ControlModifier)
                    return KEY_MOD_CONTROL;
                if (modifiers & Qt::AltModifier)
                    return KEY_MOD_ALT;
                if (modifiers & Qt::MetaModifier)
                    return MOD_SUPER;
                else
                    return KEY_MOD_UNKNOWN;
            }
    }
}
