#include "NL_ImguiInputMap.h"
#include "imgui.h"

namespace NLE
{
	namespace INPUT
	{
		int	NLEtoImguiKey(KEY key)
		{
			switch (key)
			{
			case KEY::KEY_TAB:			return ImGuiKey_Tab;      
			case KEY::KEY_LEFT:			return ImGuiKey_LeftArrow; 
			case KEY::KEY_RIGHT:		return ImGuiKey_RightArrow;
			case KEY::KEY_UP:			return ImGuiKey_UpArrow;   
			case KEY::KEY_DOWN:			return ImGuiKey_DownArrow; 
			case KEY::KEY_PAGE_UP:		return ImGuiKey_PageUp;
			case KEY::KEY_PAGE_DOWN:	return ImGuiKey_PageDown;
			case KEY::KEY_HOME:			return ImGuiKey_Home;      
			case KEY::KEY_END:			return ImGuiKey_End;       
			case KEY::KEY_DELETE:		return ImGuiKey_Delete;    
			case KEY::KEY_BACKSPACE:	return ImGuiKey_Backspace; 
			case KEY::KEY_ENTER:	
			case KEY::KEY_KP_ENTER:
										return ImGuiKey_Enter;
			case KEY::KEY_ESCAPE:		return ImGuiKey_Escape;    
			case KEY::KEY_A:			return ImGuiKey_A;         
			case KEY::KEY_C:			return ImGuiKey_C;         
			case KEY::KEY_V:			return ImGuiKey_V;         
			case KEY::KEY_X:			return ImGuiKey_X;         
			case KEY::KEY_Y:			return ImGuiKey_Y;         
			case KEY::KEY_Z:			return ImGuiKey_Z;       

			default:					return -1;
			}
			return 0;
		}
	}
}