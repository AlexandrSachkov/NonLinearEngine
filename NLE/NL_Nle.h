#ifndef NL_ENGINE_H_
#define NL_ENGINE_H_

#include "NL_INle.h"
#include "NL_DllApi.h"

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

	private:
		Nle();
		Nle(Nle const&) = delete;
		void operator=(Nle const&) = delete;

		static Nle* _nle;
		bool _initialized;
	};

#if defined (NLE_DLL) && defined(NLE_DLL_EXPORT)
	extern "C" NLE_API INle* APIENTRY GetNLE()
	{
		return &Nle::instance();
	}
#elif defined(NLE_DLL)
	extern "C" NLE_API INle* GetNLE();
#endif
}


#endif