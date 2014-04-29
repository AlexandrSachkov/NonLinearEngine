#ifndef NLRE_
#define NLRE_

#include "Container.h"

class NLRE
{
public:
	NLRE(HWND hwndVal, int widthVal, int heightVal);
	~NLRE();

	void render();

private:
	NLREDeviceController* _deviceController;
	NLRERenderingDevice* _renderingDevice;
	Container* _container;
};
#endif