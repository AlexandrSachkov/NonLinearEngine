#ifndef NL_DATA_COMPRESSION_MANAGER_H_
#define NL_DATA_COMPRESSION_MANAGER_H_

#include "NL_IConsoleQueue.h"
#include <vector>

namespace NLE
{
	class DataCompressionManager
	{
	public:
		static bool compress(CONSOLE::IConsoleQueue* console, const std::vector<char>* src, std::vector<char>*& dst);
		static bool compressFast(CONSOLE::IConsoleQueue* console, const std::vector<char>* src, std::vector<char>*& dst);
		static bool decompress(CONSOLE::IConsoleQueue* console, const std::vector<char>* src, std::vector<char>* dst);
	};
}

#endif