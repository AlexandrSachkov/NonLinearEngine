#pragma once

#include "NL_Serializer.h"
#include "NL_FileIOManager.h"

#include "cereal/types/string.hpp"
#include "cereal/types/memory.hpp"
#include "cereal/types/vector.hpp"
#include "cereal/types/unordered_map.hpp"

#include "cereal/archives/binary.hpp"
#include "cereal/archives/json.hpp"
#include "cereal/archives/xml.hpp"


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

		class CerealSerializer : public Serializer<CerealSerializer>
		{
		public:
			CerealSerializer(Form form) : _form(form)
			{
			}

			~CerealSerializer()
			{
			}

			template <class T>
			std::vector<char>* serialize(const T& obj)
			{
				std::stringstream stream;
				switch (_form)
				{
				case NLE::SERIALIZATION::BINARY:
				{
					cereal::BinaryOutputArchive archive(stream);
					archive(obj);
				}
				break;

				case NLE::SERIALIZATION::JSON:
				{
					cereal::JSONOutputArchive archive(stream);
					archive(obj);
				}
				break;

				case NLE::SERIALIZATION::XML:
				{
					cereal::XMLOutputArchive archive(stream);
					archive(obj);
				}
				break;

				default:
					assert(false);
				}
				const std::string str = stream.str();
				return new std::vector<char>(str.begin(), str.end());
			}

			template <class T>
			void deserialize(std::vector<char>* data, T& obj)
			{
				std::stringstream stream(std::string(data->begin(), data->end()));
				switch (_form)
				{
				case NLE::SERIALIZATION::BINARY:
				{
					cereal::BinaryInputArchive archive(stream);
					archive(obj);
				}
				break;

				case NLE::SERIALIZATION::JSON:
				{
					cereal::JSONInputArchive archive(stream);
					archive(obj);
				}
				break;

				case NLE::SERIALIZATION::XML:
				{
					cereal::XMLInputArchive archive(stream);
					archive(obj);
				}
				break;

				default:
					assert(false);
				}
			}

		private:
			const Form _form;
		};
	}
}
