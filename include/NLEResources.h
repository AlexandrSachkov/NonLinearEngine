#ifndef NLE_RESOURCES_
#define NLE_RESOURCES_

#if defined(_WINDOWS_VISTA_) || defined (_WINDOWS_7_) || defined(_WINDOWS_8_) || defined(_WINDOWS_8_1_)
#include <Windows.h>
	typedef HWND NLEWindowReference;
#endif

#endif