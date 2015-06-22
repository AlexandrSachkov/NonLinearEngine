#ifndef NL_DLL_API_H_
#define NL_DLL_API_H_

#if defined(_NLE_DLL_)
#include <Windows.h>
#if defined(_NLE_DLL_EXPORT_)
#define _NLE_API_ __declspec(dllexport)
#else
#define _NLE_API_ __declspec(dllimport)
#endif
#endif

#endif 