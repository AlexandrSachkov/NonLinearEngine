#ifndef NL_FILE_IO_MANAGER_H_
#define NL_FILE_IO_MANAGER_H_

#include "NL_Thread.h"
#include "NL_EngineServices.h"

#include "tbb/concurrent_queue.h"

#include <string>
#include <vector>
#include <functional>

namespace NLE
{
	namespace IO
	{
		enum OperationType
		{
			READ,
			WRITE
		};

		struct FileIOOperationDesc
		{
			FileIOOperationDesc(
				std::wstring path,
				OperationType opType,
				bool compressed,
				std::vector<char>* inputData,
				std::function<void(std::vector<char>* data)> onSuccess,
				std::function<void()> onFailure
				) :
				path(path),
				opType(opType),
				compressed(compressed),
				inputData(inputData),
				onSuccess(onSuccess),
				onFailure(onFailure)
			{
			}

			FileIOOperationDesc() :
				path(L""),
				opType(IO::READ),
				compressed(false),
				inputData(nullptr),
				onSuccess([](std::vector<char>* data) {}),
				onFailure([]() {})
			{
			}

			std::wstring path;
			OperationType opType;
			bool compressed;
			std::vector<char>* inputData;
			std::function<void(std::vector<char>* data)> onSuccess;
			std::function<void()> onFailure;
		};

#pragma pack(push, 1)
		struct NleFileHeader
		{
			NleFileHeader()
			{
				memset(_identifier, 0, 16);
				_version = 1.0f;
				_originalSize = 0;
				_compressed = false;
			}

			NleFileHeader(std::string identifier, float version, size_t originalSize, bool compressed) :
				_version(version),
				_originalSize(originalSize),
				_compressed(compressed)
			{
				memset(_identifier, 0, 16);
				strncpy(_identifier, identifier.c_str(), 16);
			}

			char _identifier[16];
			float _version;
			size_t _originalSize;
			bool _compressed;
		};
#pragma pack(pop)

		class FileIOManager
		{
		public:
			FileIOManager(NLE::EngineServices& eServices);
			~FileIOManager();
			std::wstring getFileExtension(std::wstring path);
			void read(
				std::wstring path, 
				std::function<void(std::vector<char>* data)> onSuccess, 
				std::function<void()> onFailure
				);

			void write(
				std::wstring path, 
				bool compressed,
				std::vector<char>* inputData, 
				std::function<void()> onSuccess, 
				std::function<void()> onFailure
				);
			

		private:			
			FileIOManager(FileIOManager const&) = delete;
			void operator=(FileIOManager const&) = delete;

			void fileOperation(FileIOOperationDesc& opDesc);
			void readFile(std::wstring& path, std::function<void(std::vector<char>* data)> onSuccess, std::function<void()> onFailure);
			void writeFile(std::wstring path, bool compressed, std::vector<char>* data, std::function<void(std::vector<char>* data)> onSuccess, std::function<void()> onFailure);
			std::vector<char>* decompressIfNeeded(std::wstring& path, std::vector<char>* inputBuffer);
			std::vector<char>* compressIfNeeded(std::wstring& path, bool compressed, std::vector<char>* inputBuffer);
			std::wstring getResourceIdentifier(std::wstring& path);
			bool isEngineType(const std::wstring& path);

			NLE::EngineServices& _eServices;
			Core::Thread _loadingThread;
			tbb::concurrent_queue<FileIOOperationDesc> _fileOps;
		};
	}
	
}

#endif
