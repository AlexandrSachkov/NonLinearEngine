#ifndef NL_I_SERIALIZER_H_
#define NL_I_SERIALIZER_H_

#include "NL_CerealSerializer.h"

namespace NLE
{
	namespace SERIALIZATION
	{
		typedef Serializer<CerealSerializer> ISerializer;
	}
}

#endif