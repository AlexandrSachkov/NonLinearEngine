#ifndef NL_NLE_H_
#define NL_NLE_H_

#include "NL_INle.h"
#include "NL_DllApi.h"
#include <cstdint>

struct lua_State;
namespace NLE
{
	class Nle :public INle
	{
	public:
		static INle& instance()
		{
			if (!_nle)
			{
				_nle = new Nle();
			}
			return *_nle;
		};

		~Nle();

		bool initialize();
		void release();

		void run();
		void stop();

		void attachPollEvents(void(*pollEvents)(void));
		void attachPrintConsole(void(*printConsole)(CONSOLE::OUTPUT_TYPE, const char*));
		void processEvent(INPUT::Event& event);
		void setWindowHandle(void* handle);

		void executeScript(const char* script);

	private:
		Nle();
		Nle(Nle const&) = delete;
		void operator=(Nle const&) = delete;

		static Nle* _nle;
		bool _initialized;
		uint_fast32_t _defaultGrainSize;
	};

#if defined (NLE_DLL) && defined(NLE_DLL_EXPORT)
	extern "C" NLE_API INle* APIENTRY instance()
	{
		return &Nle::instance();
	}
#elif defined(NLE_DLL)
	extern "C" NLE_API INle* instance();
#endif
}


#endif
