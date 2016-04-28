#ifndef NL_SCENE_H_
#define NL_SCENE_H_

#include <string>

namespace NLE
{
	namespace GAME
	{
		class Scene
		{
		public:
			Scene();
			~Scene();

			template<class Archive>
			void serialize(Archive& archive)
			{
				archive(
					CEREAL_NVP(_name),
					CEREAL_NVP(_uuid)
					);
			}

			std::wstring getName();

			std::string _name;
			unsigned long long _uuid;
		};
	}
}
#endif