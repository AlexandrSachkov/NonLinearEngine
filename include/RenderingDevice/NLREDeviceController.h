#ifndef NLRE_DEVICE_CONTROLLER_
#define NLRE_DEVICE_CONTROLLER_

#include "NLRERenderingDevice.h"
#include "NLRERenderingTechnique.h"
#include "NLREForwardRT.h"

class NLREDeviceController
{
public:
	NLREDeviceController(HWND hwndVal, int widthVal, int heightVal, NLRE_RENDERING_TECHNIQUE_ID techniqueId);
	NLREDeviceController(const NLREDeviceController&);
	~NLREDeviceController();
	NLRERenderingDevice* getRenderingDevice();
	bool setRenderingTechnique(NLRE_RENDERING_TECHNIQUE_ID technique);
	NLRE_RENDERING_TECHNIQUE_ID getCurrentRenderingTechniqueId();
	void render();

private:
	bool initialize();
	NLRE_RENDERING_TECHNIQUE_ID _renderingTechniqueId;
	NLRERenderingDevice _renderingDevice;
	NLRERenderingTechnique* _renderingTechnique;
};
#endif