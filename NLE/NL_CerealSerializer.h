#pragma once

#include "NL_Serializer.h"
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
			std::vector<char>* serialize(T* obj)
			{
				std::unique_ptr<T> object(obj);
				std::stringstream stream;
				switch (_form)
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
				object.release();
				const std::string str = stream.str();
				return new std::vector<char>(str.begin(), str.end());
			}

			template <class T>
			T* deserialize(std::vector<char>* data)
			{
				std::unique_ptr<T> object = nullptr;
				std::stringstream stream(std::string(data->begin(), data->end()));
				switch (_form)
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

				return object.release();
			}

		private:
			const Form _form;
		};
	}
}
