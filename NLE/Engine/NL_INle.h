#ifndef NL_IENGINE_H_
#define NL_IENGINE_H_

#include <functional>

namespace NLE
{
	namespace INPUT
	{
		struct Event;
	}
	class INle
	{
	public:
		virtual bool initialize() = 0;
		virtual void release() = 0;

		virtual void run() = 0;
		virtual void stop() = 0;

		virtual void attachPollEvents(std::function<void()> const& operation) = 0;
		virtual void processEvent(INPUT::Event& event) = 0;
		virtual void attachMakeContextCurrent(std::function<void()> const& operation) = 0;
		virtual void attachSwapBuffers(std::function<void()> const& operation) = 0;
	};
}
#endif