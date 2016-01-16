#include "NL_DataCompressionManager.h"
#include "NL_Console.h"

#include "lz4.h"
#include "lz4hc.h"

namespace NLE
{
	bool DataCompressionManager::compress(const std::vector<char>* src, std::vector<char>*& dst)
	{
		std::vector<char>* dest = new std::vector<char>(src->size());
		size_t destinationSize = (size_t)LZ4_compress_HC(&(*src)[0], &(*dest)[0], (int)src->size(), (int)dest->size(), 9);
		if (destinationSize == 0)
		{
			delete dest;
			CONSOLE::out(CONSOLE::ERR, L"Data compression failed");
			return false;
		}
		dest->resize(destinationSize);
		dst = dest;
		
		return true;
	}

	bool DataCompressionManager::compressFast(const std::vector<char>* src, std::vector<char>*& dst)
	{
		std::vector<char>* dest = new std::vector<char>(src->size());
		size_t destinationSize = (size_t)LZ4_compress_default(&(*src)[0], &(*dest)[0], (int)src->size(), (int)dest->size());
		if (destinationSize == 0)
		{
			delete dest;
			CONSOLE::out(CONSOLE::ERR, L"Data compression failed");
			return false;
		}
		dest->resize(destinationSize);
		dst = dest;

		return true;
	}

	bool DataCompressionManager::decompress(const std::vector<char>* src, std::vector<char>* dst)
	{
		if (LZ4_decompress_fast(&(*src)[0], &(*dst)[0], (int)dst->size()) <= 0)
		{
			CONSOLE::out(CONSOLE::ERR, L"Data decompression failed");
			return false;
		}

		return true;
	}
}