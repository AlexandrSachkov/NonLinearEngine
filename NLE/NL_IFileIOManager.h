#ifndef NL_I_FILE_IO_MANAGER_H_
#define NL_I_FILE_IO_MANAGER_H_

#include <string>
#include <vector>
#include <functional>

namespace NLE
{
	namespace IO
	{
		class IFileIOManager
		{
		public:
			virtual void readAsync(
				std::wstring path,
				std::function<void(std::vector<char>* data)> onSuccess,
				std::function<void()> onFailure
				) = 0;

			virtual void writeAsync(
				std::wstring path,
				std::vector<char>* inputData,
				std::function<void(std::vector<char>* data)> onSuccess,
				std::function<void(std::vector<char>* data)> onFailure
				) = 0;

			virtual bool read(std::wstring path, std::vector<char>*& dataOut) = 0;
			virtual bool write(std::wstring path, std::vector<char>* srcData) = 0;
		};
	}
}

#endif
