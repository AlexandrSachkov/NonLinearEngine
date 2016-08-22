#include "NL_SharedData.h"
#include "NL_IDataManager.h"
#include "NL_InputEvents.h"

namespace NLE
{
	namespace DATA
	{
		SharedData::SharedData(IDataManager_Data& dataManager) :
			sysExecutionTimes(dataManager, NUM_SYSTEMS, 0),

			keysPressed(dataManager, INPUT::KEY::NUM_KEYS, 0),
			keyModsPressed(dataManager, INPUT::MOD::NUM_KEY_MODS, 0),
			mouseButtonPressed(dataManager, INPUT::MOUSE::NUM_MOUSE_BUTTONS, 0),
			mouseCursorPosition(dataManager, 2, 0),
			scrollOffset(dataManager, 2, 0),
			typedCharacter(dataManager, 0)
		{
		}

		SharedData::~SharedData()
		{
		}
	}
}