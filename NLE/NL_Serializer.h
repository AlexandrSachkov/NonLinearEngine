#pragma once

#include <vector>

namespace NLE
{
	namespace SERIALIZATION
	{
		template<class T>
		class Serializer
		{
		public:
			Serializer() {}

			template <class OT>
			std::vector<char>* serialize(const OT& obj)
			{
				return static_cast<T*>(this)->serialize<OT>(obj);
			}

			template <class OT>
			void deserialize(std::vector<char>* data, OT& obj)
			{
				static_cast<T*>(this)->deserialize<OT>(data, obj);
			}
		};
	}
}