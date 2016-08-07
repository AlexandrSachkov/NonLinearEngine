#ifndef NL_I_SERIALIZER_H_
#define NL_I_SERIALIZER_H_

#include <vector>

namespace NLE
{
	namespace SERIALIZATION
	{
		class ISerializable;
		class ISerializer
		{
		public:
			virtual std::vector<char>* serialize(ISerializable* obj) = 0;
			virtual ISerializable* deserialize(std::vector<char>* data) = 0;
		};
	}
}

#endif