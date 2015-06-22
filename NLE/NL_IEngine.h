#ifndef NL_IENGINE_H_
#define NL_IENGINE_H_

namespace NLE
{
	class IEngine
	{
	public:
		virtual bool initialize() = 0;
		virtual void release() = 0;

		virtual void run() = 0;
		virtual void stop() = 0;
	};
}
#endif