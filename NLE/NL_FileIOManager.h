#ifndef NL_FILE_IO_MANAGER_H_
#define NL_FILE_IO_MANAGER_H_

#include "NL_Thread.h"

#include "tbb/concurrent_queue.h"

#include <string>
#include <vector>
#include <functional>

namespace NLE
{
	struct FileIOOperationDesc
	{
		FileIOOperationDesc(
			std::wstring path,
			bool write,
			std::vector<char>* inputData,
			std::function<void(std::vector<char>* data)> onSuccess
			) :
			path(path),
			write(write),
			inputData(inputData),
			onSuccess(onSuccess)
		{
		}

		FileIOOperationDesc() :
			path(L""),
			write(false),
			inputData(nullptr),
			onSuccess([](std::vector<char>* data) {})
		{
		}

		std::wstring path;
		bool write;
		std::vector<char>* inputData;
		std::function<void(std::vector<char>* data)> onSuccess;
	};

	struct NleFileHeader
	{
		NleFileHeader()
		{
			memset(_identifier, 0, 16);
			_version = 1.0f;
			_originalSize = 0;
		}

		NleFileHeader(std::string identifier, float version, size_t originalSize) :
			_version(version),
			_originalSize(originalSize)
		{
			memset(_identifier, 0, 16);
			strncpy(_identifier, identifier.c_str(), 16);
		}

		char _identifier[16];
		float _version;
		size_t _originalSize;
	};

	class FileIOManager
	{
	public:
		static FileIOManager& instance()
		{
			if (!_ioManager)
			{
				_ioManager = new FileIOManager();
			}
			return *_ioManager;
		}

		~FileIOManager();
		std::wstring getFileExtension(std::wstring path);
		void fileOperation(FileIOOperationDesc& opDesc);

	private:
		FileIOManager();
		FileIOManager(FileIOManager const&) = delete;
		void operator=(FileIOManager const&) = delete;

		void readFile(std::wstring& path, std::function<void(std::vector<char>* data)> onSuccess);
		void writeFile(std::wstring path, std::vector<char>* data, std::function<void(std::vector<char>* data)> onSuccess);
		std::vector<char>* decompressIfNeeded(std::wstring& path, std::vector<char>* inputBuffer);
		std::vector<char>* compressIfNeeded(std::wstring& path, std::vector<char>* inputBuffer);
		bool isCompressedType(const std::wstring& path);
		std::wstring getResourceIdentifier(std::wstring& path);

		static FileIOManager* _ioManager;
		Core::Thread _loadingThread;
		tbb::concurrent_queue<FileIOOperationDesc> _fileOps;
	};
}

#endif
