#ifndef NLRE_CONFIGURATOR_
#define NLRE_CONFIGURATOR_

/*
	Rendering Device
	1. DirectX 11:					_DX11_
	2. OpenGl 4.2:					_OPENGL4.2_		<= Unsupported
*/
#define _DX11_	

/*
	Task Management
	1. Parallel Patterns Library:	_PPL_
	2. Threading Building Blocks:	_TBB_			<= Unsupported
*/
#define _PPL_

/*
	SIMD Math library:
	1. DirectX Math:				_DXMATH_
*/
#define _DXMATH_

/*
	SIMD Collision Library:
	1. DirectX Collision			_DXCOLLISION_
*/
#define _DXCOLLISION_

/*
	Log message character max size
*/
#define _LOG_MSG_MAX_SIZE	256

#endif