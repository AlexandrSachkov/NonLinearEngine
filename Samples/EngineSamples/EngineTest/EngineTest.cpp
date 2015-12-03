#include <iostream>
#include "NL_GlfwApplicationLayer.h"

int main()
{
	NLEGlfwApplicationLayer& appLayer = NLEGlfwApplicationLayer::instance();

	appLayer.setFullscreenHint(false);
	appLayer.setWindowSizeHint(1440, 900);
	if (!appLayer.initialize())
	{
		return 0;
	}
	appLayer.run();
	appLayer.release();

	return 0;
}