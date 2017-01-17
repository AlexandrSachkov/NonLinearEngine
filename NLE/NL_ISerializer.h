#pragma once

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