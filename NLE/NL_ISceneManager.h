#ifndef NL_ISCENE_MANAGER_H_
#define NL_ISCENE_MANAGER_H_

#include "NL_ISystem.h"
#include <string>

namespace NLE
{
	namespace GRAPHICS
	{
		class Scene;
	}
	class ISceneManager : public Core::ISystem
	{
	public:
		virtual void importScene(std::wstring& path) = 0;
		virtual GRAPHICS::Scene* getGScene() = 0;
	};
}

#endif