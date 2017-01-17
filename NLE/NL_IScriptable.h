#pragma once

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