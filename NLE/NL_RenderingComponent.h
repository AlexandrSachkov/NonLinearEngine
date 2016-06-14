#ifndef NL_RENDERING_COMPONENT_H_
#define NL_RENDERING_COMPONENT_H_

#include "NL_GameObjectComponent.h"

namespace NLE
{
	namespace GAME
	{
		class RenderingComponent : public GameObjectComponent
		{
		public:
			RenderingComponent(GameObject* parent);
			~RenderingComponent();
		};
	}
}

#endif