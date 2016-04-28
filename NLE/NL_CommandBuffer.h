#ifndef NL_COMMAND_BUFFER_H_
#define NL_COMMAND_BUFFER_H_

#include "NL_Queue.h"

#include <unordered_map>
#include <functional>
#include <assert.h>

namespace NLE
{
	template<class T>
	class CommandBuffer
	{
	public:
		CommandBuffer()
		{
		}

		~CommandBuffer()
		{
		}

		void queueCommand(unsigned int key, T command)
		{
			_commands.push(std::make_pair<>(key, command ));
		}

		void addFunction(unsigned int key, std::function<void(T)> function)
		{
			auto iter = _functions.find(key);
			if (iter != _functions.end())
			{
				assert(false && "Command Buffer: Function already exists.");
			}
			else
			{
				_functions.insert(std::make_pair<>(key, function ));
			}		
		}

		void processCommands()
		{
			std::pair<unsigned int, T> keyCommand;
			while (_commands.pop(keyCommand))
			{
				auto iter = _functions.find(keyCommand.first);
				if (iter != _functions.end())
				{
					(iter->second)(keyCommand.second);
				}
				else
				{
					assert(false && "Command Buffer: Unsupported command.");
				}
			}
		}

	private:
		Queue<std::pair<unsigned int, T>> _commands;
		std::unordered_map<unsigned int, std::function<void(T)>> _functions;
	};
}

#endif