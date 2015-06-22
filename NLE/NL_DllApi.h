#ifndef NL_DLL_API_H_
#define NL_DLL_API_H_

#if defined(NLE_DLL)
#include <Windows.h>
#if defined(NLE_DLL_EXPORT)
#define NLE_API __declspec(dllexport)
#else
#define NLE_API __declspec(dllimport)
#endif
#endif

#endif 