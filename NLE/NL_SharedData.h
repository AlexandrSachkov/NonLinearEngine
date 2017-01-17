#pragma once

#include "NL_SharedEntry.h"
#include "NL_SharedArray.h"

namespace NLE
{
	enum SYSTEMS
	{
		INPUT_PROCESSOR,
		GAME_MANAGER,
		RENDERING_ENGINE,
		UI_MANAGER,
		SCRIPTING_ENGINE,
		DATA_MANAGER,

		NUM_SYSTEMS
	};
	namespace DATA
	{
		


		class IDataManager_Data;
		class SharedData
		{
		public:
			SharedData(IDataManager_Data& dataManager);
			~SharedData();

			//Engine
			SharedArray<double> sysExecutionTimes;


			//Input
			SharedArray<bool> keysPressed;
			SharedArray<bool> keyModsPressed;
			SharedArray<bool> mouseButtonPressed;
			SharedArray<double> mouseCursorPosition;
			SharedArray<double> scrollOffset;
		};
	}
}
