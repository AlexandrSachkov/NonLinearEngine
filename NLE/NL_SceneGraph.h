#pragma once

#include <string>
#include <vector>
#include <unordered_map>

namespace NLE
{
	namespace GAME
	{
		struct SceneGraphDesc
		{

		};

		class GameObject;
		class SceneGraph
		{
		public:
			SceneGraph();
			~SceneGraph();

			template<class Archive>
			void save(Archive& archive) const
			{
				/*archive(
					CEREAL_NVP(name),
					CEREAL_NVP(_scriptingContext)
					);*/
			}

			template<class Archive>
			void load(Archive& archive)
			{
				/*archive(
					CEREAL_NVP(name),
					CEREAL_NVP(_scriptingContext)
					);*/
			}

			void addObject(GameObject* object);
			void addObject(GameObject* parent, GameObject* object);
			void removeObject(std::string name);
			void removeObject(GameObject* object);
			GameObject* getObject(std::string name);

		private:
			std::unordered_map<std::string, GameObject*> _objects;
			std::vector<GameObject*> _root;
		};
	}
}