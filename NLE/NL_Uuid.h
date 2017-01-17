#pragma once

#include <chrono>

namespace NLE
{
	namespace UUID
	{
		static unsigned long long generateUuid()
		{
			auto time = std::chrono::high_resolution_clock::now();
			return time.time_since_epoch().count();
		}
	}	
}