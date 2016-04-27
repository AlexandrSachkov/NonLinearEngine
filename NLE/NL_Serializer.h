#ifndef NL_SERIALIZER_H_
#define NL_SERIALIZER_H_

#include "NL_FileIOManager.h"

#include "cereal/archives/binary.hpp"
#include "cereal/archives/json.hpp"
#include "cereal/archives/xml.hpp"
#include "cereal/types/string.hpp"
#include "cereal/types/memory.hpp"

#include <fstream>
#include <assert.h>

namespace NLE
{
	namespace SERIALIZATION
	{
		enum Form
		{
			BINARY,
			JSON,
			XML
		};

		class Serializer
		{
		public:
			Serializer()
			{
			}

			~Serializer()
			{
			}

			template <class T>
			std::vector<char>* serialize(std::unique_ptr<T>& object, Form form)
			{
				std::stringstream stream;
				switch (form)
				{
				case NLE::SERIALIZATION::BINARY:
				{
					cereal::BinaryOutputArchive archive(stream);
					archive(object);
				}
				break;

				case NLE::SERIALIZATION::JSON:
				{
					cereal::JSONOutputArchive archive(stream);
					archive(object);
				}
				break;

				case NLE::SERIALIZATION::XML:
				{
					cereal::XMLOutputArchive archive(stream);
					archive(object);
				}
				break;

				default:
					assert(false);
				}
				const std::string str = stream.str();
				return new std::vector<char>(str.begin(), str.end());
			}

			template <class T>
			std::unique_ptr<T> deserialize(std::vector<char>* data, Form form)
			{
				std::unique_ptr<T> object = nullptr;
				std::stringstream stream(std::string(data->begin(), data->end()));
				switch (form)
				{
				case NLE::SERIALIZATION::BINARY:
				{
					cereal::BinaryInputArchive archive(stream);
					archive(object);
				}
				break;

				case NLE::SERIALIZATION::JSON:
				{
					cereal::JSONInputArchive archive(stream);
					archive(object);
				}
				break;

				case NLE::SERIALIZATION::XML:
				{
					cereal::XMLInputArchive archive(stream);
					archive(object);
				}
				break;

				default:
					assert(false);
				}

				return std::move(object);
			}
		};
	}
}

#endif
