#include <iostream>
#include "NL_GlfwApplicationLayer.h"

int main()
{
	NLEGlfwApplicationLayer& appLayer = NLEGlfwApplicationLayer::instance();

	appLayer.setFullscreenHint(true);
	appLayer.setWindowSizeHint(1920, 1080);//(1440, 900);
	if (!appLayer.initialize())
	{
		return 0;
	}
	appLayer.run();

	return 0;
}