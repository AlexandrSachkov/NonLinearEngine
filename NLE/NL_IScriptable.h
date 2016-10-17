#ifndef NL_I_SCRIPTABLE_H_
#define NL_I_SCRIPTABLE_H_

#include <cereal/types/polymorphic.hpp>
#include <LuaIntf.h>

namespace NLE
{
	namespace SCRIPT
	{
		class IScriptable
		{
		public:
			virtual void bind(LuaIntf::CppBindModule<LuaIntf::LuaBinding>& binding) = 0;
			virtual ~IScriptable() {}
		};
	}
}


#endif