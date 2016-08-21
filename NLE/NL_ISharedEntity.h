#ifndef NL_I_SHARED_ENTITY_H_
#define NL_I_SHARED_ENTITY_H_

namespace NLE
{
	namespace DATA
	{
		class ISharedEntity
		{
		public:
			virtual void sync() = 0;
		};
	}
}

#endif