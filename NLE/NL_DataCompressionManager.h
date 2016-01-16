#ifndef NL_DATA_COMPRESSION_MANAGER_H_
#define NL_DATA_COMPRESSION_MANAGER_H_

#include <vector>

namespace NLE
{
	class DataCompressionManager
	{
	public:
		static bool compress(const std::vector<char>* src, std::vector<char>*& dst);
		static bool compressFast(const std::vector<char>* src, std::vector<char>*& dst);
		static bool decompress(const std::vector<char>* src, std::vector<char>* dst);
	};
}

#endif