#ifndef NL_EVENT_QUEUE_H_
#define NL_EVENT_QUEUE_H_

#include "NL_InputEvents.h"
#include "tbb/concurrent_queue.h"

namespace NLE
{
	namespace INPUT
	{
		class EventQueue
		{
		public:
			EventQueue()
			{
			}

			~EventQueue()
			{
			}

			void push(Event& event)
			{
				_events.push(event);
			}

			bool pop(Event& event)
			{
				return _events.try_pop(event);
			}

			void clear()
			{
				_events.clear();
			}

		private:
			tbb::concurrent_queue<Event> _events;
		};
	}
}

#endif