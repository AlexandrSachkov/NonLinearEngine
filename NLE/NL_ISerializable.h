#ifndef NL_I_SERIALIZABLE_H_
#define NL_I_SERIALIZABLE_H_

namespace NLE
{
	namespace SERIALIZATION
	{
		class ISerializable
		{
		public:
			virtual void save() = 0;
			virtual void load() = 0;
		};
	}
}

#endif