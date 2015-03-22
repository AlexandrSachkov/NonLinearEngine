#include "NL_UScene.h"
#include "NL_SScene.h"
#include "NL_UObject.h"

namespace NLE
{
	namespace Core
	{
		UScene::UScene() : _sysScenes()
		{

		}

		UScene::~UScene()
		{

		}

		bool UScene::initialize()
		{
			return true;
		}

		void UScene::release()
		{

		}

		void UScene::attachScene(uint_fast8_t sysId, SScene* scene)
		{
			_sysScenes.insert(std::pair<uint_fast8_t, SScene*>(sysId, scene));
		}

		void UScene::addObject(UObject* object)
		{
			for (const auto& sceneLocator : _sysScenes)
			{
				sceneLocator.second->addObject(object->getSysObject(sceneLocator.first));
			}
		}
	}
}