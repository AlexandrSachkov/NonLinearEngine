#pragma once

#include "NL_Queue.h"

#include <unordered_map>
#include <functional>
#include <assert.h>

namespace NLE
{
	class OperationBuffer
	{
	public:
		OperationBuffer()
		{
		}

		~OperationBuffer()
		{
		}

		void queueOperation(std::function<void()> op)
		{
			_operations.push(op);
		}

		void replayOperations()
		{
			std::function<void()> op;
			while (_operations.pop(op))
			{
				op();
			}
		}

	private:
		Queue<std::function<void()>> _operations;
	};
}