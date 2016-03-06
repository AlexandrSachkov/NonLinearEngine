#ifndef NL_THREAD_LOCAL_H_
#define NL_THREAD_LOCAL_H_

#include "NL_ScriptExecutor.h"
#include "NL_Timer.h"

#include "tbb\enumerable_thread_specific.h"

#include <string>
#include <locale>
#include <codecvt>

namespace NLE
{
	namespace TLS
	{
		typedef tbb::enumerable_thread_specific<std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>> StringConverter;
		static StringConverter strConverter;

		typedef tbb::enumerable_thread_specific<SCRIPT::ScriptExecutor> ScriptExecutor;
		static ScriptExecutor scriptExecutor;

		typedef tbb::enumerable_thread_specific<Timer> PerformanceTimer;
		static PerformanceTimer performanceTimer;
	}
}

#endif
