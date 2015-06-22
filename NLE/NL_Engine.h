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

#if defined (NLE_DLL) && defined(NLE_DLL_EXPORT)
	extern "C" NLE_API IEngine* APIENTRY GetNLE()
	{
		return &Engine::instance();
	}
#elif defined(NLE_DLL)
	extern "C" NLE_API IEngine* GetNLE();
#endif
}


#endif