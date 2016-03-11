#ifndef NL_GAME_OBJECT_H_
#define NL_GAME_OBJECT_H_

#include <string>

namespace NLE
{
	namespace GAME
	{
		class RenderingComponent;
		class UiComponent;
		class ScriptingComponent;
		class GameObject
		{
		public:
			GameObject();
			~GameObject();

		private:
			RenderingComponent* _renderingComponent;
			UiComponent* _uiComponent;
			ScriptingComponent* _scriptingComponent;

			std::wstring _name;
			const unsigned long long _uuid;
		};
	}
}

#endif
