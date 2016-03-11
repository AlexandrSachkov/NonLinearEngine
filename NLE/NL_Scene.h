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

		private:
			std::wstring _name;
			const unsigned long long _uuid;
		};
	}
}
#endif