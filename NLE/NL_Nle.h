#ifndef NL_NLE_H_
#define NL_NLE_H_

#include "NL_CommonTypes.h"

#include "tbb/atomic.h"

#include <cstdint>
#include <memory>
#include <string>

struct lua_State;
namespace tbb
{
	class spin_mutex;
}
namespace NLE
{
	class Nle
	{
	public:
		static Nle& instance()
		{
			if (!_nle)
			{
				_nle = new Nle();
			}
			return *_nle;
		};

		~Nle();

		bool initialize(Size2D screenSize, bool fullscreen, bool decorated, std::wstring title);
		void release();

		void run();
		void stop();

	private:
		Nle();
		Nle(Nle const&) = delete;
		void operator=(Nle const&) = delete;

		static Nle* _nle;
		bool _initialized;
		uint_fast32_t _defaultGrainSize;

		tbb::atomic<bool> _running;
	};
}


#endif
