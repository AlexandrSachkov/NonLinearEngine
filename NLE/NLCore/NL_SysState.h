#ifndef NL_SYS_STATE_H_
#define NL_SYS_STATE_H_


namespace NLE
{
	namespace Core
	{

		class SysState
		{
		public:
			virtual ~SysState(){}
			virtual void update() = 0;
		};
	}
}


#endif