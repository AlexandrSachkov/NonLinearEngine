#ifndef NLRE_DEVICE_CONTROLLER_
#define NLRE_DEVICE_CONTROLLER_

#include "NLRERenderingDevice.h"

class NLREDeviceController
{
public:
	NLREDeviceController(HWND hwndVal, int widthVal, int heightVal);
	NLREDeviceController(const NLREDeviceController&);
	~NLREDeviceController();
private:

	NLRERenderingDevice _renderingDevice;
};
#endif