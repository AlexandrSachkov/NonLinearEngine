#ifndef NL_LUA_CUSTOM_TYPES_H_
#define NL_LUA_CUSTOM_TYPES_H_

#include "NL_ThreadLocal.h"
#include "LuaIntf.h"

namespace LuaIntf
{
	template <>
	struct LuaTypeMapping <std::wstring>
	{
		static void push(lua_State* L, const std::wstring& str)
		{
			if (str.empty()) {
				lua_pushliteral(L, "");
			}
			else {
				std::string buf = NLE::TLS::strConverter.local().to_bytes(str);
				lua_pushlstring(L, buf.data(), buf.length());
			}
		}

		static std::wstring get(lua_State* L, int index)
		{
			size_t len;
			const char* p = luaL_checklstring(L, index, &len);
			return NLE::TLS::strConverter.local().from_bytes(p, p + len);
		}

		static std::wstring opt(lua_State* L, int index, const std::wstring& def)
		{
			return lua_isnoneornil(L, index) ? def : get(L, index);
		}
	};

}

#endif