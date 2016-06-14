#ifndef NL_SCENE_H_
#define NL_SCENE_H_

#include "NL_ScriptingContext.h"
#include "NL_Map.h"

#include <string>
#include "NL_ThreadLocal.h"

namespace NLE
{
	namespace GAME
	{
		class GameObject;
		class Scene
		{
		public:
			Scene();
			~Scene();

			template<class Archive>
			void save(Archive& archive) const
			{
				auto& cnv = TLS::strConverter.local();
				auto name = cnv.to_bytes(_name);
				archive(
					CEREAL_NVP(name),
					CEREAL_NVP(_uuid)
					);
			}

			template<class Archive>
			void load(Archive& archive)
			{
				auto& cnv = TLS::strConverter.local();
				std::string name;
				archive(
					CEREAL_NVP(name),
					CEREAL_NVP(_uuid)
					);

				_name = cnv.from_bytes(name);
			}

			std::wstring getName();
			void setName(std::wstring name);
			void addObject(GameObject* object);
			GameObject* getObject(unsigned long long uuid);
			SCRIPT::ScriptingContext& getScriptingContext();

		private:
			std::wstring _name;
			unsigned long long _uuid;
			Map<unsigned long long, GameObject*, REPLACE> _objects;
			SCRIPT::ScriptingContext _scriptingContext;
		};
	}
}
#endif