#ifndef NL_ISCENE_MANAGER_H_
#define NL_ISCENE_MANAGER_H_

#include "NLCore\NL_ISystem.h"
#include <string>

namespace NLE
{
	class ISceneManager : public Core::ISystem
	{
	public:
		virtual bool importScene(std::wstring& path) = 0;
	};
}

#endif