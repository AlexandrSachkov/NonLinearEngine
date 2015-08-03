#ifndef NL_IENGINE_H_
#define NL_IENGINE_H_

#include <functional>
#include <cstdint>
#include <string>

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

		virtual void setWindowHandle(void* handle) = 0;
		virtual void setScreenDimensions(uint_fast32_t width, uint_fast32_t height) = 0;
		virtual void setFullscreen(bool fullscreen) = 0;

		virtual bool importScene(std::wstring& path) = 0;
	};
}
#endif