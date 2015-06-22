#ifndef NL_ENGINE_H_
#define NL_ENGINE_H_

#include "NL_IEngine.h"
#include "NL_DllApi.h"

namespace NLE
{
	class Engine :public IEngine
	{
	public:
		static IEngine& instance()
		{
			if (!_nle)
			{
				_nle = new Engine();
			}
			return *_nle;
		};

		~Engine();

		bool initialize();
		void release();

		void run();
		void stop();

	private:
		Engine();
		Engine(Engine const&) = delete;
		void operator=(Engine const&) = delete;

		static Engine* _nle;
		bool _initialized;
	};

#if defined (_NLE_DLL_) && defined(_NLE_DLL_EXPORT_)
	extern "C" _NLE_API_ IEngine* APIENTRY GetNLE()
	{
		return &Engine::instance();
	}
#elif defined(_NLE_DLL_)
	extern "C" _NLE_API_ IEngine* GetNLE();
#endif
}


#endif