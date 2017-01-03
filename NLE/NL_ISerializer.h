#ifndef NL_I_SERIALIZER_H_
#define NL_I_SERIALIZER_H_

#include "NL_CerealSerializer.h"
#include <memory>

namespace NLE
{
	namespace SERIALIZATION
	{
		typedef Serializer<CerealSerializer> ISerializer;
		typedef std::shared_ptr<ISerializer> ISerializerSP;
	}
}

#endif