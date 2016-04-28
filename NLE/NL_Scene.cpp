#include "NL_Scene.h"
#include "NL_Uuid.h"
#include "NL_ThreadLocal.h"

namespace NLE
{
	namespace GAME
	{
		Scene::Scene() :
			_uuid(UUID::generateUuid())
		{
			_name = "Scene " + std::to_string(_uuid);
		}

		Scene::~Scene()
		{

		}

		std::wstring Scene::getName()
		{
			TLS::StringConverter::reference converter = TLS::strConverter.local();
			return converter.from_bytes(_name);
		}
	}
}