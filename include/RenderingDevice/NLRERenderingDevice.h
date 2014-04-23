#ifndef NLRE_RENDERING_DEVICE_
#define NLRE_RENDERING_DEVICE_

#include "stdafx.h"

#ifdef _DX11_
	#include "DX11Device\NLREDX11RenderingDevice.h"
	typedef NLREDX11RenderingDevice NLRERenderingDevice;
#endif


#endif