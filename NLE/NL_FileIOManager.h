#ifndef NL_FILE_IO_MANAGER_H_
#define NL_FILE_IO_MANAGER_H_

#include <string>
#include <vector>

namespace NLE
{
	class FileIOManager
	{
	public:
		static bool readFile(std::wstring path, std::vector<char>*& data);
		static bool writeFile(std::wstring path, const std::vector<char>* data);
	};
}

#endif
