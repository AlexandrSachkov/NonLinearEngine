#ifndef NL_SCENE_GRAPH_H_
#define NL_SCENE_GRAPH_H_

#include "NL_Map.h"
#include <string>
#include <vector>

namespace NLE
{
	namespace GAME
	{
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
			Map<std::string, GameObject*, KEEP_EXISTING> _objects;
			std::vector<GameObject*> _root;
		};
	}
}

#endif