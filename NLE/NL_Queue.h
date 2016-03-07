#ifndef NL_QUEUE_H_
#define NL_QUEUE_H_

#include "tbb/concurrent_queue.h"

namespace NLE
{
	template<typename T>
	class Queue
	{
	public:
		Queue()
		{
		}

		~Queue()
		{
		}

		void push(T& event)
		{
			_events.push(event);
		}

		bool pop(T& event)
		{
			return _events.try_pop(event);
		}

		void clear()
		{
			_events.clear();
		}

	private:
		tbb::concurrent_queue<T> _events;
	};
}

#endif