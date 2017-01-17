#ifndef NL_I_FILE_IO_MANAGER_H_
#define NL_I_FILE_IO_MANAGER_H_

#include <string>
#include <vector>
#include <functional>
#include <memory>

#include "NL_LuaCustomTypes.h"
#include "LuaIntf.h"

namespace NLE
{
	namespace IO
	{
		class IFileIOManager_EService
		{
		public:
			virtual std::vector<char>* read(std::string path) = 0;
			virtual bool write(std::string path, std::vector<char>* srcData) = 0;

			static void attachMasterBindings(LuaIntf::CppBindModule<LuaIntf::LuaBinding>& binding)
			{
				binding.beginClass<IFileIOManager_EService>("FileIOManager")
					.addFunction("read", &IFileIOManager_EService::read)
					.addFunction("write", &IFileIOManager_EService::write)
					.endClass();
			}
		};

		class IFileIOManager : public IFileIOManager_EService
		{
		public:			
			virtual ~IFileIOManager() {};
		};

		typedef std::shared_ptr<IFileIOManager> IFileIOManagerSP;
		typedef std::shared_ptr<IFileIOManager_EService> IFileIOManager_EServiceSP;
	}
}

#endif
