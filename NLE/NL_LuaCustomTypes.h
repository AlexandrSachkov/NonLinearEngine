#ifndef NL_LUA_CUSTOM_TYPES_H_
#define NL_LUA_CUSTOM_TYPES_H_

#include "NL_ThreadLocal.h"
#include "LuaIntf.h"

#include <vector>
#include <unordered_map>
#include <memory>

namespace LuaIntf
{
	LUA_USING_SHARED_PTR_TYPE(std::shared_ptr)
	LUA_USING_LIST_TYPE(std::vector)
	LUA_USING_MAP_TYPE(std::unordered_map)
}

#endif