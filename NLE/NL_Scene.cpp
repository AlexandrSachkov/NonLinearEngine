#include "NL_Scene.h"
#include "NL_Uuid.h"

namespace NLE
{
	namespace GAME
	{
		Scene::Scene() :
			_uuid(UUID::generateUuid())
		{
			_name = L"Scene " + std::to_wstring(_uuid);
		}

		Scene::~Scene()
		{

		}
	}
}