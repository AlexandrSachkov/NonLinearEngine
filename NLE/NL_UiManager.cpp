#include "NL_UiManager.h"
#include "NL_Console.h"
#include "NL_ThreadLocal.h"
#include "NL_DeviceCore.h"
#include "NL_Systems.h"
#include "NL_SysInitializer.h"

#include "lua.hpp"

#include <assert.h>
#include <string>

namespace NLE
{
	namespace UI
	{
		UiManager::UiManager() :
			_initialized(false)
		{
		}

		UiManager::~UiManager()
		{
		}

		bool UiManager::initialize(std::unique_ptr<Core::SysInitializer> const& initializer)
		{
			assert(!_initialized && _printConsole);

			TLS::ScriptExecutor::reference executor = TLS::scriptExecutor.local();
			executor.registerCallback("NLE_ui_getData", uiGetData);
			executor.registerCallback("NLE_ui_setData", uiSetData);

			_procedure = [&]() {
				CONSOLE::Console::instance().outputConsole();

				TLS::ScriptExecutor::reference executor = TLS::scriptExecutor.local();
				
				std::pair<std::string, int(*)(lua_State* state)> callback;
				while (_callbacks.try_pop(callback))
				{
					executor.registerCallback(callback.first, callback.second);
				}

				std::string script;
				while (_scripts.try_pop(script))
				{				
					executor.executeScript(script.c_str());
				}			
			};

			_initialized = true;
			return _initialized;
		}

		void UiManager::start()
		{

		}

		void UiManager::stop()
		{

		}

		void UiManager::release()
		{
			_initialized = false;
		}

		bool UiManager::initialized()
		{
			return _initialized;
		}

		std::function<void()> const& UiManager::getExecutionProcedure()
		{
			return _procedure;
		}

		Core::ISystem& UiManager::getInterface()
		{
			return *this;
		}

		int UiManager::uiGetData(lua_State* state)
		{
			return static_cast<UI::UiManager*>(&Core::DeviceCore::instance().getSystemInterface(SYS::SYS_UI_MANAGER))
				->getData(state);
		}

		int UiManager::uiSetData(lua_State* state)
		{
			return static_cast<UI::UiManager*>(&Core::DeviceCore::instance().getSystemInterface(SYS::SYS_UI_MANAGER))
				->setData(state);
		}

		int UiManager::getData(lua_State* state)
		{
			lua_settop(state, 1);
			if (lua_isstring(state, 1))
			{
				std::string dataId = lua_tostring(state, 1);
				if (dataId.compare("fps") == 0)
				{
					//lua_pushnumber(state, (*_fps)[0]);
					return 0;
				}
				else if (dataId.compare("canvasBgColor") == 0)
				{
					/*DirectX::XMFLOAT4 canvasColor = (*_canvasBgColor)[0];
					lua_pushnumber(state, canvasColor.x);
					lua_pushnumber(state, canvasColor.y);
					lua_pushnumber(state, canvasColor.z);
					lua_pushnumber(state, canvasColor.w);*/
					return 0;
				}
				else
				{
					CONSOLE::out(CONSOLE::ERR, "Data ID not supported: " + dataId);
					return 0;
				}				
			}
			return 0;
		}

		int UiManager::setData(lua_State* state)
		{
			if (lua_isstring(state, 1))
			{
				std::string dataId = lua_tostring(state, 1);
				if (dataId.compare("canvasBgColor") == 0)
				{			
					/*DirectX::XMFLOAT4 canvasColor = DirectX::XMFLOAT4(
						(float)lua_tonumber(state, 2),
						(float)lua_tonumber(state, 3),
						(float)lua_tonumber(state, 4),
						(float)lua_tonumber(state, 5)
						);*/
					return 0;
				}
				else
				{
					CONSOLE::out(CONSOLE::ERR, "Data ID not supported: " + dataId);
					return 0;
				}
			}
			return 0;
		}

		void UiManager::bindScriptCallback(const char* name, int(*callback)(lua_State* state), bool async)
		{
			if (async)
			{
				_callbacks.push(std::make_pair<>(name, callback));
			}
			else
			{
				TLS::ScriptExecutor::reference executor = TLS::scriptExecutor.local();
				executor.registerCallback(name, callback);
			}
		}

		void UiManager::executeScript(const char* script, bool async)
		{
			if (async)
			{
				_scripts.push(script);
			}
			else
			{
				TLS::ScriptExecutor::reference executor = TLS::scriptExecutor.local();
				executor.executeScript(script);
			}			
		}
	}
}